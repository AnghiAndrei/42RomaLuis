// leaderboard.js

export async function initLeaderboard() {
  const data = await fetchLeaderboard();
  if (data) {
    populateLeaderboard(data);
  }
}

function createLeaderboardRow(user) {
  const tr = document.createElement("tr");
  tr.className = `leaderboar__user leaderboard__user--${user.rank}`;

  tr.innerHTML = `
    <td data-column="Player Details">
      <div class="hstack" style="display: flex; gap: 1rem; align-items: center; justify-content: flex-start; flex-direction: row;">
        <a class="avatar-link link hint--top" aria-label="@${user.username}" href="/player/${user.username}">
          <div style="position: relative">
            <div class="avatar-link__image avatar-link__image--pro">
              <img src="${user.avatarUrl}" alt="${user.username} avatar" class="leaderboard__user-avatar" width="32" height="32" />
            </div>
          </div>
        </a>
        <div style="display: flex; gap: 0.25rem; align-items: center">
          <a class="name-link" href="/player/${user.username}">
            <span class="leaderboard__user-name">${user.name}</span>
          </a>
        </div>
      </div>
    </td>
    <td data-column="Score">${user.score}</td>
    <td data-column="Meta">(${user.meta})</td>
    <td data-column="Rank">#${user.rank}</td>
  `;

  return tr;
}

function populateLeaderboard(users) {
  const leaderboardBody = document.getElementById("leaderboard-body");
  leaderboardBody.innerHTML = ""; // Clear existing rows

  users.forEach((user) => {
    const row = createLeaderboardRow(user);
    leaderboardBody.appendChild(row);
  });
}

async function fetchLeaderboard() {
  try {
    const response = await fetch("/game/leaderboard");
    if (response.status === 200) {
      return await response.json();
    }
  } catch (error) {
    console.error(error);
  }
}
