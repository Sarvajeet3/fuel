Fuel
====

“If a game engine could run anywhere, how would the world change?”_

Fuel was born from this single question.

`Fuel` is a minimal C89 game engine with multi-arch JIT,
hardware-accelerated rendering backends, and platform-native audio
pipelines — built for production deployment.

It runs on [any post-2000 computer,](docs/porting.md)
from under-resourced hardware to cutting-edge systems.

---

## Quick Start

* [Downloads](https://github.com/awemorris/fuel/releases)
* [Getting Started](docs/gettingstarted.md)
* [Documentation](docs/index.md)

---

## ✨ Key Features

* **Jot & Run** — No boilerplates. Jot down an idea, and it comes alive.
* **Lightweight** — Runs even on small or older machines.
* **Ultra Fast** — Built-in JIT compiler brings ultra speed into your code.
* **Go Far, Stay Close** — Develop for distant platforms, with nothing but your own machine.

---

## 🧪 Example

Here's a [simple sample](sample/main.fuel) showing how to display an
image at the mouse position.

---

## What's Fuel?

Fuel is a lightweight and flexible game engine, designed to support
creators across desktop, mobile, and console platforms.

It runs smoothly even on older or low-spec machines — if you have a
computer, there's a place for you to create. 💻🌱

And if you're using something more powerful, like a modern MacBook or
iPhone, Fuel adapts to draw out the full capabilities of your
device. 🎮📱

You don't need the latest hardware. Fuel helps you go beyond your
environment. It's a helpful companion for creators everywhere —
especially in places with fewer resources.

Create at your pace, wherever you are in the world. 🌍✨

---

## Technical Overview

### Core Architecture

* **Engine Core**: Written in C89, portable and dependency-free.
* **Scripting**: Uses `FuelLang`, a custom language designed for clarity and fast execution.
* **JIT Compilation**: Built-in JIT for many architectures, with optional AOT for mobile platforms.
* **Rendering**: Supports DirectX 9/11/12, Metal, OpenGL, and a fallback software renderer.
* **Audio**: Lightweight backend supporting DirectSound, Audio Unit, ALSA, and others.
* **Small Footprint**: Runtime is less than 2MB.

### Platform Support

|Platform Type  |OS / Platform       |Notes                                     |
|---------------|--------------------|------------------------------------------|
|Desktop        |Windows             |Supports DirectX                          |
|               |macOS               |Supports Metal                            |
|               |Linux               |Supports OpenGL                           |
|               |FreeBSD             |Supports OpenGL                           |
|Mobile         |iOS                 |Source export for Xcode projects          |
|               |Android             |Source export for Android Studio projects |
|Console        |Nintendo Switch™   |NDA license required                      |
|               |PlayStation® 5     |NDA license required                      |
|               |Xbox Series X\|S    |NDA license required                      |
|Web            |WebAssembly         |Supports WebGL                            |

### FuelLang

`FuelLang` (/ˈfjʊəlæŋ/, "fyool-lang") is a lightweight scripting
language designed specifically for Fuel. Featuring a game-oriented
syntax, it emphasizes clarity, instant startup, and seamless
integration with the engine.

Built-in JIT compiler supports multiple architectures:
**x86, x86_64, Arm32, Arm64, PowerPC32, PowerPC64, MIPS32, and MIPS64.**

For platforms where JIT is restricted, its C source backend enables
AOT compilation, making it ideal for mobile deployment.

---

## License Overview

Fuel uses dual-licensing.

### Open Source License

Fuel is available as open-source software under the MIT License.
You're free to use, modify, and share it — even in commercial projects.
Please see the [LICENSE](LICENSE) file in the repository for full details.

Support is provided on a best-effort, community-driven basis.
If you require guaranteed support, please contact the author to discuss an agreement.

### Commercial Console License

On commercial game platforms such as Nintendo Switch™, PlayStation® 5,
and Xbox Series X|S, the terms of each platform's SDK agreement may
restrict the use of open-source libraries that are not expressly
authorized by the platform holder.

To support compliance with such requirements, an NDA-based proprietary
license of Fuel is available under the following conditions:

* Eligibility: Available to licensed developers with access to the official SDK and a signed NDA with Nintendo, Sony, or Microsoft.
* Distribution: A commercial version of Fuel is provided privately upon request and is not included in the public repository.
* Usage: The provided code may be integrated into your project and submitted as part of your own source code to satisfy platform submission requirements.

To request access, please contact the author with proof of your platform NDA status and a description of your development environment.

---

## Why Fuel?

Fuel is for those who quietly hold a dream, and wish to share it, one
small step at a time.

Creativity shouldn't depend on the power of your computer, where you
live, or what tools you have.

Fuel was created with the hope that every creator deserves space to
explore, no matter their surroundings.

Whether you're using a Raspberry Pi in a classroom, or using a
UN-issued Chromebook in a temporary shelter, Fuel offers gentle tools
to help bring your ideas to life — in a way that feels simple,
thoughtful, and yours. If you have something to make, Fuel will be
here to walk with you.

Dreams fuel it — and they're the only requirement.

---

## 🤝 Join Us

Fuel is still in its early stages. We're building a game engine with
care, hoping it will inspire and empower creators around the world.

If you're interested in contributing — whether it's code,
documentation, testing, or ideas — we'd be happy to have you with us.

Every small step helps shape what Fuel can become. You're welcome to
join us on this journey.

[Join us on Discord](https://discord.gg/ybHWSqDVEX)

---

## About the Author

Awe (/aːwe/, "ah-weh") is a programmer living alone in a small house,
surrounded by fields. They love writing code — it feels simple and
clear.  Understanding people's feelings takes time, but tools can be
kind.

This software is Awe's small universe. Thank you for visiting. And
thank you for receiving their seasoned craftsmanship.

Please use this dream-fueled engine with confidence.
It was made for you, even before we met.
