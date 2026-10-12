# Advanced UI Menus

![Unreal Engine](https://img.shields.io/badge/Engine-Unreal%20Engine%205.7-0E1128?style=for-the-badge&logo=unrealengine&logoColor=white)
![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![UI](https://img.shields.io/badge/UI-UMG%20%7C%20Blueprints-8A2BE2?style=for-the-badge)

A modular main menu and settings framework developed in **Unreal Engine 5.7 using C++ and UMG**. This project focuses on creating organized, reusable UI systems with Blueprint-editable layouts, centralized management, and support for keyboard, mouse, and controller input.

---

## 🛠 Project Details

- **Engine:** Unreal Engine 5.7
- **Language:** C++
- **UI Framework:** Unreal Motion Graphics (UMG)
- **Architecture:** UObject-based managers and a centralized Service Locator Subsystem
- **Input:** Keyboard, mouse, and controller support
- **Project Type:** Main Menu and Settings Framework

---

## 📑 Table of Contents

- [Project Overview](#-project-overview)
- [Features](#-features)
- [Core Systems](#-core-systems)
- [Architecture Overview](#-architecture-overview)
- [UI Design](#-ui-design)
- [Technical Goals](#-technical-goals)
- [Project Status](#-project-status)
- [Contact](#-contact)

---

## 🎮 Project Overview

Advanced UI Menus is a C++-based Unreal Engine project focused on building a structured main menu and settings experience.

The goal is to keep gameplay logic and UI management organized in C++, while allowing widget layouts and visual design to remain editable through Unreal Engine's Blueprint editor.

Instead of placing all menu behavior inside individual widgets, the project uses dedicated managers to handle menu navigation, settings, saving, and input-related responsibilities.

This approach is intended to make the UI easier to maintain, expand, and reuse across future projects.

---

## ✨ Features

### Main Menu System

- Main menu navigation and state management.
- Transitions between the main menu, settings, and credits.
- Back navigation using a state stack.
- Camera transitions for menu presentation.
- Centralized management of menu widgets and menu states.

### Settings System

- General, Graphics, Audio, and Controls settings categories.
- Resolution selection and window mode configuration.
- VSync and frame rate limit options.
- Master, music, and sound effects volume controls.
- Saving and restoring settings.
- Unsaved changes tracking and a reset-to-defaults workflow.

### Input and Navigation

- Keyboard and mouse input support.
- Controller input detection and navigation support.
- Input prompt widgets for displaying relevant control hints.
- Development of an input remapping interface using Enhanced Input.

### UI Development

- C++-driven widget behavior.
- Blueprint-editable widget layouts.
- Reusable UI components.
- Separation of visual presentation from management logic.

---

## ⚙️ Core Systems

### Main Menu Manager

Responsible for coordinating the main menu experience, including widget setup, menu navigation, and state transitions.

The system uses a current menu state alongside a state stack to support navigation between menu screens and returning to previous states.

### Settings Manager

Coordinates the settings interface and manages settings-related behavior.

Responsibilities include:

- Switching between settings categories.
- Managing graphics and audio options.
- Tracking changes to settings.
- Applying settings and coordinating saving.
- Restoring saved values or resetting settings to defaults.

### Settings Save Manager

Separates settings persistence from the UI and settings-management logic.

The goal is to provide a dedicated system for loading and saving player settings without placing save-game responsibilities inside individual widgets.

### Input Mapping Manager

Provides a dedicated location for input mapping and remapping functionality using Unreal Engine's Enhanced Input system.

The intended design keeps gameplay input configuration separate from the UI code responsible for displaying remapping controls.

### Input Device Manager

Tracks the active input device so the UI can respond to keyboard/mouse or controller input.

This supports adapting input prompts to the device being used.

---

## 🏗️ Architecture Overview

The project uses a centralized Service Locator Subsystem to create and provide access to the different manager objects.

The intended relationship between the systems is:

```text
Service Locator Subsystem
          |
          |-- Main Menu Manager
          |      |-- Main Menu Widget
          |      |-- Settings Widget
          |      |-- Credits Widget
          |
          |-- Settings Manager
          |      |-- Graphics Settings
          |      |-- Audio Settings
          |      |-- Controls Settings
          |
          |-- Settings Save Manager
          |
          |-- Input Mapping Manager
          |
          |-- Input Device Manager
```

The managers are responsible for coordinating behavior, while the widgets handle user interaction and visual presentation.

This separation helps avoid placing the entire UI system inside one class and makes individual systems easier to develop and debug.

---

## 🎨 UI Design

The project uses Unreal Motion Graphics (UMG) for its interface and C++ for the underlying behavior.

The design goal is to combine the flexibility of Blueprint widget layouts with the structure and maintainability of C++.

This allows visual elements to be adjusted in the editor without requiring every layout change to be made through code.

---

## 🧠 Technical Goals

This project explores several important Unreal Engine development concepts:

- C++ and UMG integration.
- UObject-based system architecture.
- Centralized service and manager organization.
- State machines and state-stack navigation.
- Settings management and SaveGame persistence.
- Enhanced Input integration.
- Controller-friendly UI navigation.
- Separation of UI presentation and gameplay logic.
- Reusable and maintainable code.

---

## 🚧 Project Status

**In Development**

The project is being developed incrementally, with an emphasis on creating a reliable foundation for menu navigation, settings management, and input support.

Future improvements include expanding input remapping, refining controller navigation, and continuing to improve the modularity and reusability of the framework.

---

## 📧 Contact

- **Developer:** Brandin Stanfield
- **Email:** [Brandin.Stanfield@gmail.com](mailto:Brandin.Stanfield@gmail.com)
- **GitHub:** [malicehightopp1](https://github.com/malicehightopp1)
- **Project Repository:** [AdvancedUIMenus](https://github.com/malicehightopp1/AdvancedUIMenus)
