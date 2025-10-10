
# OpLink

**OpLink** is a C++/Qt-based demonstrator application built on top of the [PlugFrame](https://github.com/elekdom/PlugFrame) modular framework. It showcases the capability to develop service-oriented client/server software by leveraging PlugFrame’s dynamic plugin and service mechanisms.

## Key Concepts

OpLink follows a **service-oriented architecture**, where the system is composed of modular units (bundles) that provide or consume services at runtime. It is designed to illustrate:
- A **backend server** providing hardware-related or control-oriented services.
- A **frontend GUI client** enabling human interaction.
- A **shared communication layer** based on TCP socket services offered by PlugFrame.

## Architecture Overview

The application is divided into two main execution domains:

- **Backend Server**:
  - Provides core system services (e.g., device simulation, logging, user authentication).
  - Headless by default (no GUI).
  - Bundles include `simulator`, `users`, `logger`, etc.

- **Frontend GUI Client**:
  - Built using Qt's GUI module (QWidgets).
  - Provides user interface to monitor and interact with backend services.
  - Connects to the backend over TCP using a dedicated client-side bundle.

Both sides leverage PlugFrame’s dynamic service registration and communication APIs.

## Requirements

- Qt 5.15
- `qmake` build system
- C++17 compatible compiler
- Linux (tested on Ubuntu 24.04)

## Repository Layout

```
oplink/
├── backend-bundles/        # OpLink server bundles
├── backend-launcher        # OpLink server launcher
├── core-backend-lib        # OpLink server dynamic library
├── core-lib                # OpLink dynamic library for both server and client
├── frontend-bundles        # OpLink client bundles
├── frontend-launcher       # OpLink client launcher
├── scripts/                # Tools for deployment
├── .img/                   # Screenshots and graphical assets
└── oplink.pro              # Qt project file for OpLink
```

## Cloning Instructions

OpLink is a sub-project of PlugFrame. You must **clone PlugFrame first**, and then clone OpLink into the `applications/` subdirectory of PlugFrame:

```bash
# Clone the PlugFrame main repository
git clone https://github.com/elekdom/PlugFrame.git
cd PlugFrame/applications

# Clone OpLink inside PlugFrame
git clone https://github.com/elekdom/OpLink.git
```

Your resulting structure should look like:

```
ELEKDOM-PlugFrame/
├── applications/
│   └── OpLink/
├── plugframe/
│   └── bundles/
│   └── core-lib/
│   └── launcher/
```

## Build Instructions

The recommended approach is to use **Qt Creator** with "shadow build" enabled.

Alternatively, from the root of PlugFrame, you may use:

```bash
mkdir build
cd build
qmake ../PlugFrame
make -j$(nproc)
```

Ensure that PlugFrame is built before attempting to build OpLink.

## Deployment Structure

After a successful build and deployment (via the `install_oplink.py` script), the binary layout follows this structure under the `bin/` directory:

```
bin/
├── libs/                    # Shared dynamic libraries from PlugFrame and OpLink
├── oplink_backend/         # Server-side executable (non-GUI)
└── oplink_guifrontend/     # Client-side GUI application
```

- The `libs/` directory contains all shared libraries from both PlugFrame and OpLink.
- The `oplink_backend/` directory includes the **server executable**, typically running without a GUI.
- The `oplink_guifrontend/` directory contains the **graphical client application** for user interaction.

## License

OpLink is released under the GNU General Public License v3.0 (GPLv3).

(c) ELEKDOM 2023–2025
