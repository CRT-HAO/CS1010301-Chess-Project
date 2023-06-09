let soundBGM = new Audio("./sound/bgm.mp3");
let soundClick = new Audio("./sound/click.mp3");
let soundMove = new Audio("./sound/move.mp3");

function stopAllSound() {
  soundBGM.pause();
  soundBGM.currentTime = 0;
}

function playBGM() {
  soundBGM.currentTime = 0;
  soundBGM.loop = true;
  soundBGM.play();
}

function playClickSound() {
  if (soundClick.paused) soundClick.play();
  soundClick.currentTime = 0;
}

function playMoveSound() {
  if (soundMove.paused) soundMove.play();
  soundMove.currentTime = 0;
}
