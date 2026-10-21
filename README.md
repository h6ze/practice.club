<div align="center">

<img width="250" height="250" alt="morphineflist" src="https://github.com/user-attachments/assets/0cd32ccc-c6a2-48dd-b02b-aa0d9371d435" />

# practice.club

**a cheat for hood warfare 2. its an unreal 5 game. its not good.**

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Visual Studio 2022](https://img.shields.io/badge/Visual_Studio-2022-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white)
![DX12](https://img.shields.io/badge/overlay-DX12-2F855A?style=for-the-badge)
![x64](https://img.shields.io/badge/arch-x64-444?style=for-the-badge)

</div>

---

this was supposed to be a p2c we were going to sell. but after a while we js couldnt
support selling a cheat for a game this bad, so it isnt one anymore. here, free. youre welcome. love u

dx12 overlay, imgui menu, hooks `UObject::ProcessEvent` for the game thread and the swapchain for drawing.
built off a 5.8.3 dump, offsets regen from it. no esp, no server spoofing, no anticheat games just the
games own shi turned past where theyre supposed to go.

---

## features

too many to list properly, its basically every setting the game has plus the ones it tries to hide.
grouped by menu tab:

| tab | what |
|---|---|
| you | movement speed, fly, jump, view + fov, aimbot / silent aim (both draw a fov circle) |
| weapons | damage, fire rate, range, mag, recoil, hitscan, headshot, skins |
| kit | throwables, items, attachments |
| progress | level, xp, unlocks, stats, save / load |
| match | host control score, round, state, rules, player list |
| modes | objectives, spawning, game mode settings |
| bots | bot tiers, aim, perception, memory |
| streaks | killstreak activate + place + rules |
| online | quick play settings, network |
| media | camera record, spectator, pause |
| world | lights, post process, fog, sky, atmosphere |
| dev | debug, report + probe buttons |

---

## building it yourself

**stuff you need**

| | |
|---|---|
| windows | 10 or 11, x64 |
| [visual studio](https://visualstudio.microsoft.com/downloads/) | 2022, community is fine |
| workload | **Desktop development with C++** |

**build it**

1. open `runtime\gang gang.sln`
2. config dropdown to `Ship` or `Dev`, platform `x64`
3. **Build → Build Solution** (`Ctrl+Shift+B`)
4. dll comes out at `runtime\bin\Ship\practice.club.dll`

**the two configs**

| config | what its for |
|---|---|
| `Dev` | no ltcg, fast rebuilds. use this while youre working on it |
| `Ship` | full opt + ltcg. slower to build, ship this |

x64 only. theres no win32 and there wont be.

---

## usage

- inject the dll into hood warfare 2 with whatever you use. let the game load in first
- `Delete` opens / closes the menu
- a console comes up with it for logs
- menu layout, panel positions and your accent colour save to a config
- logs and crash reports land in `%LOCALAPPDATA%\practice.club\logs\`

---

## if it doesnt work

| problem | fix |
|---|---|
| build error about the platform toolset | vs installer → modify → tick **MSVC v143** |
| cant find the windows sdk | same screen, tick **Windows 11 SDK** |
| injects but no menu | you injected too early, load into the game fully first |
| crashes the second it injects | offsets are dead, check the crashlog in the logs folder |

---

## layout

```
runtime/
  code/
    client/ boot, bridge, diag, platform, render (dx12, imgui), util
    features/ the actual cheat, grouped combat / player / match / world
    sdk/ hand-written unreal + hw2 overlays, offsets regen'd from a dump
  vendor/ imgui, detours
  build/ msbuild props + dev/ship configs
  bin/ build output
```

---

<div align="center">
<sub>the game is bad. dont pay anyone for this.</sub>
</div>
