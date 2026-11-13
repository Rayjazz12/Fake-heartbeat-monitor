// scripts/build.js — Node build script for the Fake Heartbeat Monitor mod.
// Usage: node scripts/build.js [Debug|Release] [--clean]

const { execSync } = require("child_process");
const fs = require("fs");
const path = require("path");

const root = __dirname + "/../..";
const cfg = process.argv[2] || "Release";
const clean = process.argv.includes("--clean");

if (clean) {
    ["build", "dist", "settings.json"].forEach((d) => {
        const p = path.join(root, d);
        if (fs.existsSync(p)) {
            fs.rmSync(p, { recursive: true, force: true });
            console.log(`[clean] removed ${p}`);
        }
    });
    console.log("Clean done.");
    process.exit(0);
}

if (!fs.existsSync(path.join(root, "mod.json"))) {
    console.error("[build] mod.json not found. Run from repo root.");
    process.exit(1);
}

console.log(`[build] Geode mod → ${cfg}`);

try {
    execSync("geode build --config " + cfg, { cwd: root, stdio: "inherit" });
} catch (e) {
    console.error("[build] failed to build.");
    process.exit(1);
}

const outDir = path.join(root, "dist");
fs.mkdirSync(outDir, { recursive: true });
fs.writeFileSync(path.join(root, ".build-done"), new Date().toISOString());
console.log("[build] done.");
