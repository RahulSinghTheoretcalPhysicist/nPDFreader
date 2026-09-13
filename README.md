# PDF Reader for Windows 11

Phase 1 of a native C++/Qt PDF reader and basic editor.

## What Phase 1 already contains

- Native Qt 6 Widgets application.
- Windows-style main window.
- File/Open PDF chooser.
- Document viewport shell.
- Menus, toolbar, status bar, navigation/zoom placeholders.
- Modular source layout.
- CMake build system.
- GitHub Actions Windows x64 build.
- `windeployqt` packaging of required Qt runtime DLLs.
- Downloadable portable ZIP artifact containing `PDFReader.exe`.

The selected PDF is **not rendered yet**. That is intentional. PDFium integration is Phase 2.

## Toolchain

- C++20
- Qt 6.11.2 Widgets
- CMake 3.24+
- MSVC / Visual Studio 2022
- Windows x64

## Repository layout

```text
PDFReader/
├── .github/
│   └── workflows/
│       └── windows-build.yml
├── src/
│   ├── main.cpp
│   └── ui/
│       ├── DocumentCanvas.cpp
│       ├── DocumentCanvas.h
│       ├── MainWindow.cpp
│       └── MainWindow.h
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Compile automatically on GitHub

1. Create a new GitHub repository.
2. Upload the contents of this project so `CMakeLists.txt` is at the repository root.
3. Commit/push to the `main` branch.
4. Open the repository's **Actions** tab.
5. Open **Build Windows x64**.
6. The workflow installs Qt, configures CMake, compiles with MSVC, runs `windeployqt`, creates a portable ZIP, and uploads it as an Actions artifact.
7. Download the artifact named `PDFReader-Windows-x64`.
8. Extract the ZIP and run `PDFReader.exe` on Windows 11 x64.

You can also run the workflow manually with **Actions → Build Windows x64 → Run workflow**.

## Why PDFium is not in Phase 1

The first milestone isolates the application framework from the PDF engine. The UI, viewport, build pipeline, deployment, and directory structure should be known-good before introducing a large native dependency. Phase 2 will add a `pdf/` layer around PDFium rather than allowing PDFium calls to leak throughout the UI.

## Next engineering milestone

Phase 2 will add:

```text
src/pdf/PdfEngine
src/pdf/PdfDocument
src/pdf/PdfPage
src/pdf/PdfRenderer
```

The flow will become:

```text
Open PDF
   ↓
PdfDocument loads PDFium document
   ↓
Read page count and first-page geometry
   ↓
PdfRenderer renders page 0 into a BGRA bitmap
   ↓
Convert safely to QImage
   ↓
DocumentCanvas displays the actual PDF page
```

## Qt licensing note

Qt is a separate dependency with its own licensing terms. If this application is distributed beyond private/internal use, review the Qt open-source/commercial licensing obligations that apply to the way Qt is linked and distributed.
