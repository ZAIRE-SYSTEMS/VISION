let ZState = {
  userName: "ZAIRE Rider",
  avatarInitials: "ZR",

  btConnected: true,
  btDeviceName: "Yann’s Phone",
  btAutoConnect: true,
  btAudioActive: true,

  photosCount: 12,
  videosCount: 3,
  mediaLastTime: "14:32",

  topSpeed: 42.6,
  topHeight: 312,
  topAccel: 1.9,

  walkiePeers: [{}, {}, {}]
};

function setActiveNav(activeBtn) {
  document.querySelectorAll(".nav-item").forEach(btn => {
    btn.classList.remove("nav-item--active");
  });
  activeBtn.classList.add("nav-item--active");
}

function showView(viewId, navBtn) {
  document
    .querySelectorAll("#dashboard-view, #media-view, #walkie-view, #settings-view")
    .forEach(v => v.classList.add("hidden"));

  document.getElementById(viewId).classList.remove("hidden");
  setActiveNav(navBtn);
}

function renderDashboard() {
  document.getElementById("dash-username").textContent = ZState.userName;
  document.querySelector("#dash-avatar span").textContent = ZState.avatarInitials;

  document.getElementById("bt-state").textContent =
    ZState.btConnected ? "Connected" : "Disconnected";

  document.getElementById("bt-device-name").textContent = ZState.btDeviceName;
  document.getElementById("bt-autoconnect").textContent =
    ZState.btAutoConnect ? "ON" : "OFF";
  document.getElementById("bt-audio").textContent =
    ZState.btAudioActive ? "Active" : "Idle";

  document.getElementById("photos-count").textContent = ZState.photosCount;
  document.getElementById("videos-count").textContent = ZState.videosCount;
  document.getElementById("media-last").textContent = ZState.mediaLastTime;

  document.getElementById("top-speed").textContent = ZState.topSpeed.toFixed(1);
  document.getElementById("top-height").textContent = ZState.topHeight;
  document.getElementById("top-accel").textContent = ZState.topAccel.toFixed(1);
  document.getElementById("walkie-peers").textContent = ZState.walkiePeers.length;
}

document.addEventListener("DOMContentLoaded", () => {
  renderDashboard();

  document.getElementById("nav-dashboard").onclick = () =>
    showView("dashboard-view", document.getElementById("nav-dashboard"));

  document.getElementById("nav-media").onclick = () =>
    showView("media-view", document.getElementById("nav-media"));

  document.getElementById("nav-walkie").onclick = () =>
    showView("walkie-view", document.getElementById("nav-walkie"));

  document.getElementById("nav-settings").onclick = () =>
    showView("settings-view", document.getElementById("nav-settings"));

  document.getElementById("media-card").onclick = () =>
    showView("media-view", document.getElementById("nav-media"));
});
