# Fake Heartbeat Monitor

A minimal Geometry Dash Geode mod that draws an in-level **fake heartbeat monitor** HUD: a big red heart with a large lime-green BPM number on a dark leaning card with a thick white border.

## Features

- **Believable BPM**: reads in steps of 2–3 bpm — it never jumps 100 → 101, it jumps 100 → 102 / 100 → 103.
- **Hold after death**: when you die on a level with a high BPM, the monitor holds that high BPM for a moment instead of immediately dropping to a low BPM, then relaxes slowly to resting.
- **Settings** (configurable at runtime): resting/peak BPM, step size, read speed, keeps-rate-on-death, death hold, death recovery, plus styling corner/margin/scale/opacity/colour.
- **Standalone in-level HUD**: no menu popup, just a floating heart-rate widget over the level.

## Install

1. Drop the `.geode` file into Geometry Dash's `mods` folder (or use the in-game mod browser).
2. Requires **Geode >= 5.11.2**.

## Build

- **Windows (dev machine):** install the Geode SDK and VS 2022 C++ workload, then `.\build.ps1`.
- **GitHub Actions:** push to `master`; `.github/workflows/build.yml` builds and releases the `.geode`.

## Settings

| Setting | Default | Meaning |
|---|---|---|
| restingBpm | 82 | BPM when relaxed |
| peakBpm | 137 | BPM when maxed out |
| step | 3 | Step size in bpm (never ±1) |
| readSpeed | 1.0 | Speed of new readings |
| keepsRateOnDeath | true | Hold BPM after death |
| deathHold | 2.2 | Hold duration in seconds |
| deathRecovery | 95.0 | Decay time constant |
| corner | 1 | HUD corner (1 = Top Left) |
| margin | 10 | HUD margin in px |
| scale | 1.0 | HUD scale |
| opacity | 82 | HUD opacity (0-255) |
| colour | #a6de00 | BPM colour (hex) |
