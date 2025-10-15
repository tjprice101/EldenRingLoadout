#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include "Loadout.h"
#include "LoadoutSaver.h"
#include "LoadoutLoader.h"

namespace fs = std::filesystem;

// GLFW error callback
static void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main()
{
    // --- Setup GLFW ---
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char *glsl_version = "#version 130";
    GLFWwindow *window = glfwCreateWindow(1400, 900, "Elden Ring Loadout Manager", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // --- Setup ImGui ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    // --- Loadout Data ---
    Stats stats(1, 10, 10, 10, 10, 10, 10, 10, 10);
    Physic physic("Bubble1", "Bubble2");
    Loadout currentLoadout(stats, physic);
    char loadoutName[128] = "";

    // Weapon buffers
    char rightHandNames[3][64] = {"", "", ""};
    char rightHandAsh[3][64] = {"", "", ""};
    char rightHandAffinity[3][64] = {"", "", ""};
    int rightHandLevel[3] = {1, 1, 1};

    char leftHandNames[3][64] = {"", "", ""};
    char leftHandAsh[3][64] = {"", "", ""};
    char leftHandAffinity[3][64] = {"", "", ""};
    int leftHandLevel[3] = {1, 1, 1};

    // Armor buffers
    char armorNames[5][64] = {"", "", "", "", ""};
    char armorTypes[5][64] = {"", "", "", "", ""};

    // Talismans
    char talismanNames[4][64] = {"", "", "", ""};

    // Spells (expanded to 14)
    char spellNames[14][64] = {"", "", "", "", "", "", "", "", "", "", "", "", "", ""};

    // Physic
    char bubbleTear1[64] = "Bubble1";
    char bubbleTear2[64] = "Bubble2";

    // Stats
    int level = 1, vigor = 10, mind = 10, endurance = 10, strength = 10, dexterity = 10, intelligence = 10, faith = 10, arcane = 10;

    bool showCreateWindow = false, showLoadWindow = false, exitProgram = false;
    bool confirmDelete = false;
    std::vector<std::string> savedLoadouts;
    std::string selectedLoadout = "";

    // --- Main Loop ---
    while (!glfwWindowShouldClose(window) && !exitProgram)
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Main Menu Window ---
        ImGui::Begin("Elden Ring Loadout Manager");

        if (ImGui::Button("Create New Loadout"))
            showCreateWindow = true;

        ImGui::SameLine();
        if (ImGui::Button("Load Existing Loadout"))
        {
            showLoadWindow = true;
            savedLoadouts.clear();
            if (fs::exists("Saved Loadouts"))
            {
                for (auto &p : fs::directory_iterator("Saved Loadouts"))
                    if (p.path().extension() == ".txt")
                        savedLoadouts.push_back(p.path().stem().string());
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Exit Program"))
            exitProgram = true;

        ImGui::Separator();

        // Display loaded loadout info if any
        if (!selectedLoadout.empty())
        {
            ImGui::Text("Loaded Loadout: %s", selectedLoadout.c_str());
            ImGui::Separator();

            // Weapons
            ImGui::Text("Right Hand Weapons:");
            for (int i = 0; i < 3; i++)
            {
                Weapon *w = currentLoadout.getRightHandWeapon(i);
                if (w)
                    ImGui::Text("%d: %s, %s, %s, Lv %d", i + 1, w->getName().c_str(), w->getAshOfWar().c_str(), w->getAffinity().c_str(), w->getLevel());
            }

            ImGui::Text("Left Hand Weapons:");
            for (int i = 0; i < 3; i++)
            {
                Weapon *w = currentLoadout.getLeftHandWeapon(i);
                if (w)
                    ImGui::Text("%d: %s, %s, %s, Lv %d", i + 1, w->getName().c_str(), w->getAshOfWar().c_str(), w->getAffinity().c_str(), w->getLevel());
            }

            // Armor
            ImGui::Text("Armor Set:");
            ArmorSet &armorSet = currentLoadout.getArmorSet();
            for (size_t i = 0; i < armorSet.size(); i++)
            {
                Armor a = armorSet.getArmor(i);
                ImGui::Text("%s: %s", a.getTypeOfArmor().c_str(), a.getName().c_str());
            }

            // Talismans
            ImGui::Text("Talismans:");
            Talismans &talismans = currentLoadout.getTalismans();
            for (size_t i = 0; i < talismans.size(); i++)
            {
                Talisman t = talismans.getTalisman(i);
                ImGui::Text("%s", t.getName().c_str());
            }

            // --- Spells Section ---
            ImGui::Text("Spells");
            ImGui::Separator();
            ImGui::BeginChild("Spells", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);

            for (int i = 0; i < 14; i++)
            {
                ImGui::InputText(("Spell " + std::to_string(i + 1)).c_str(), spellNames[i], IM_ARRAYSIZE(spellNames[i]));
            }

            ImGui::EndChild();

            // Physic
            ImGui::Text("Physic: %s, %s", currentLoadout.getPhysic().getBubbleTear1().c_str(), currentLoadout.getPhysic().getBubbleTear2().c_str());

            // Stats
            Stats s = currentLoadout.getStats();
            ImGui::Text("Stats: Lv %d, Vig %d, Mind %d, End %d, Str %d, Dex %d, Int %d, Faith %d, Arc %d",
                        s.getLevel(), s.getVigor(), s.getMind(), s.getEndurance(), s.getStrength(),
                        s.getDexterity(), s.getIntelligence(), s.getFaith(), s.getArcane());

            // Delete button
            if (ImGui::Button("Delete Loadout"))
                confirmDelete = true;
        }

        // Delete confirmation
        if (confirmDelete)
        {
            ImGui::OpenPopup("Confirm Delete");
            if (ImGui::BeginPopupModal("Confirm Delete", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Are you sure you want to delete '%s'?", selectedLoadout.c_str());
                if (ImGui::Button("Yes"))
                {
                    fs::remove("Saved Loadouts/" + selectedLoadout + ".txt");
                    selectedLoadout.clear();
                    confirmDelete = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("No"))
                {
                    confirmDelete = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }

        ImGui::End();

        // --- Create Loadout Window ---
        if (showCreateWindow)
        {
            ImGui::SetNextWindowSize(ImVec2(1300, 800), ImGuiCond_FirstUseEver);
            ImGui::Begin("Create New Loadout", &showCreateWindow, ImGuiWindowFlags_AlwaysAutoResize);

            // Loadout Name
            ImGui::InputText("Loadout Name", loadoutName, IM_ARRAYSIZE(loadoutName));
            ImGui::Separator();

            if (ImGui::BeginTable("LoadoutColumns", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable))
            {
                // Column 1: Weapons
                ImGui::TableNextColumn();
                ImGui::Text("Right Hand Weapons");
                ImGui::Separator();
                ImGui::BeginChild("RightHandWeapons", ImVec2(0, 250), true);
                for (int i = 0; i < 3; i++)
                {
                    ImGui::InputText(("Name##R" + std::to_string(i)).c_str(), rightHandNames[i], IM_ARRAYSIZE(rightHandNames[i]));
                    ImGui::InputText(("Ash of War##R" + std::to_string(i)).c_str(), rightHandAsh[i], IM_ARRAYSIZE(rightHandAsh[i]));
                    ImGui::InputText(("Affinity##R" + std::to_string(i)).c_str(), rightHandAffinity[i], IM_ARRAYSIZE(rightHandAffinity[i]));
                    ImGui::InputInt(("Level##R" + std::to_string(i)).c_str(), &rightHandLevel[i]);
                    ImGui::Separator();
                }
                ImGui::EndChild();

                ImGui::Text("Left Hand Weapons");
                ImGui::Separator();
                ImGui::BeginChild("LeftHandWeapons", ImVec2(0, 250), true);
                for (int i = 0; i < 3; i++)
                {
                    ImGui::InputText(("Name##L" + std::to_string(i)).c_str(), leftHandNames[i], IM_ARRAYSIZE(leftHandNames[i]));
                    ImGui::InputText(("Ash of War##L" + std::to_string(i)).c_str(), leftHandAsh[i], IM_ARRAYSIZE(leftHandAsh[i]));
                    ImGui::InputText(("Affinity##L" + std::to_string(i)).c_str(), leftHandAffinity[i], IM_ARRAYSIZE(leftHandAffinity[i]));
                    ImGui::InputInt(("Level##L" + std::to_string(i)).c_str(), &leftHandLevel[i]);
                    ImGui::Separator();
                }
                ImGui::EndChild();

                // Column 2: Armor & Talismans
                ImGui::TableNextColumn();
                ImGui::Text("Armor Set");
                ImGui::Separator();
                ImGui::BeginChild("ArmorSet", ImVec2(0, 300), true);
                const char *armorParts[5] = {"Head", "Chest", "Arms", "Legs", "Accessory"};
                for (int i = 0; i < 5; i++)
                {
                    ImGui::InputText((std::string("Type##A") + std::to_string(i)).c_str(), armorTypes[i], IM_ARRAYSIZE(armorTypes[i]));
                    ImGui::InputText((std::string("Name##A") + std::to_string(i)).c_str(), armorNames[i], IM_ARRAYSIZE(armorNames[i]));
                    ImGui::Separator();
                }
                ImGui::EndChild();

                ImGui::Text("Talismans");
                ImGui::Separator();
                ImGui::BeginChild("Talismans", ImVec2(0, 150), true);
                for (int i = 0; i < 4; i++)
                    ImGui::InputText(("Talisman " + std::to_string(i + 1)).c_str(), talismanNames[i], IM_ARRAYSIZE(talismanNames[i]));
                ImGui::EndChild();

                // Column 3: Spells, Physic & Stats
                ImGui::TableNextColumn();

                ImGui::Text("Spells");
                ImGui::Separator();
                ImGui::BeginChild("Spells", ImVec2(0, 300), true);
                for (int i = 0; i < 14; i++)
                    ImGui::InputText(("Spell " + std::to_string(i + 1)).c_str(), spellNames[i], IM_ARRAYSIZE(spellNames[i]));
                ImGui::EndChild();

                ImGui::Text("Physic");
                ImGui::Separator();
                ImGui::BeginChild("Physic", ImVec2(0, 100), true);
                ImGui::InputText("Bubble Tear 1", bubbleTear1, IM_ARRAYSIZE(bubbleTear1));
                ImGui::InputText("Bubble Tear 2", bubbleTear2, IM_ARRAYSIZE(bubbleTear2));
                ImGui::EndChild();

                ImGui::Text("Stats");
                ImGui::Separator();
                ImGui::BeginChild("Stats", ImVec2(0, 250), true);
                ImGui::InputInt("Level", &level);
                ImGui::InputInt("Vigor", &vigor);
                ImGui::InputInt("Mind", &mind);
                ImGui::InputInt("Endurance", &endurance);
                ImGui::InputInt("Strength", &strength);
                ImGui::InputInt("Dexterity", &dexterity);
                ImGui::InputInt("Intelligence", &intelligence);
                ImGui::InputInt("Faith", &faith);
                ImGui::InputInt("Arcane", &arcane);
                ImGui::EndChild();

                ImGui::EndTable();
            }

            ImGui::Separator();

            if (strlen(loadoutName) > 0)
            {
                if (ImGui::Button("Save Loadout", ImVec2(-1, 50)))
                {
                    // --- Weapons ---
                    for (int i = 0; i < 3; i++)
                    {
                        if (strlen(rightHandNames[i]) > 0)
                            currentLoadout.setRightHandWeapon(i, new Weapon(rightHandNames[i], rightHandAsh[i], rightHandAffinity[i], rightHandLevel[i]));
                        if (strlen(leftHandNames[i]) > 0)
                            currentLoadout.setLeftHandWeapon(i, new Weapon(leftHandNames[i], leftHandAsh[i], leftHandAffinity[i], leftHandLevel[i]));
                    }

                    // --- Armor ---
                    ArmorSet &armorSet = currentLoadout.getArmorSet();
                    armorSet.clear();
                    for (int i = 0; i < 5; i++)
                        if (strlen(armorNames[i]) > 0 || strlen(armorTypes[i]) > 0)
                            armorSet.addArmor(Armor(armorTypes[i], armorNames[i]));

                    // --- Talismans ---
                    Talismans &talismans = currentLoadout.getTalismans();
                    talismans.clear();
                    for (int i = 0; i < 4; i++)
                        if (strlen(talismanNames[i]) > 0)
                            talismans.addTalisman(Talisman(talismanNames[i]));

                    // --- Spells ---
                    Spells &spells = currentLoadout.getSpells();
                    spells.clear();
                    for (int i = 0; i < 14; i++)
                        if (strlen(spellNames[i]) > 0)
                            spells.addSpell(Spell(spellNames[i]));

                    // --- Physic ---
                    currentLoadout.getPhysic().setBubbleTear1(bubbleTear1);
                    currentLoadout.getPhysic().setBubbleTear2(bubbleTear2);

                    // --- Stats ---
                    currentLoadout.getStats() = Stats(level, vigor, mind, endurance, strength, dexterity, intelligence, faith, arcane);

                    // --- Save to file ---
                    if (LoadoutSaver::saveLoadout(currentLoadout, loadoutName))
                        std::cout << "Loadout saved successfully!\n";
                    else
                        std::cout << "Failed to save loadout.\n";

                    // Close the window after saving
                    showCreateWindow = false;
                    selectedLoadout = loadoutName;
                }
            }
            else
            {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Enter a Loadout Name to enable Save");
            }

            ImGui::End(); // End Create Loadout window
        }

        // --- Load Loadout Window ---
        if (showLoadWindow)
        {
            ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
            ImGui::Begin("Load Existing Loadout", &showLoadWindow);
            if (savedLoadouts.empty())
            {
                ImGui::Text("No loadouts found.");
            }
            else
            {
                ImGui::BeginChild("LoadoutsList", ImVec2(0, 0), true);
                for (size_t i = 0; i < savedLoadouts.size(); i++)
                {
                    if (ImGui::Button(savedLoadouts[i].c_str()))
                    {
                        if (LoadoutLoader::loadLoadout(currentLoadout, savedLoadouts[i]))
                        {
                            std::cout << "Loaded: " << savedLoadouts[i] << "\n";
                            selectedLoadout = savedLoadouts[i];
                        }
                        else
                        {
                            std::cout << "Failed to load: " << savedLoadouts[i] << "\n";
                        }
                        showLoadWindow = false;
                    }
                }
                ImGui::EndChild();
            }
            ImGui::End();
        }

        // --- Rendering ---
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // --- Cleanup ---
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
