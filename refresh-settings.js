// scripts/refresh-settings.js — refreshes the settings on load (standalone monitor).

const fs = require("fs");
const path = require("path");

const root = __dirname + "/../..";
const settingsFile = path.join(root, "settings.json");

const settings = {
    corner: 1,
    margin: 10,
    scale: 1.0,
    opacity: 82,
    colour: "#a6de00",
    rateTitle: "RATE",
    restingBpm: 82,
    peakBpm: 137,
    bpmStep: 3,
    readSpeed: 1.0,
    keepsRateOnDeath: true,
    deathHold: 2.2,
    deathRecovery: 95.0
};

fs.writeFileSync(settingsFile, JSON.stringify(settings, null, 2) + "\n", "utf8");
console.log("[settings] refreshed from mod.json defaults.");
