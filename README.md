![logo](https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/4d23d7ba-d33a-4e83-b912-e2fdc20a0dd9)
# CS1010301-Chess-Project
111.2 CS1010301 物件導向程式設計實習 西洋棋遊戲  
An original chess game.  
Written in C++ with web technology based GUI.  
<img width="1485" alt="截圖 2023-05-25 下午4 47 40" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/2fc406f1-01dd-4a2a-acf6-ebf154a79f25">
<img width="1529" alt="截圖 2023-05-25 下午4 48 02" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/3b0bbd6d-1d00-4774-84e3-9bea52b2586d">
<img width="1572" alt="截圖 2023-05-20 上午4 39 40" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/62e27d56-d0a4-4361-8ffe-ae5047f75dd7">
<img width="1572" alt="截圖 2023-05-20 上午4 40 23" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/38275a54-e52a-42ea-9678-beefe6da2998">

## Support Platforms
 - Windows MSVC
 - MacOS AppleClang
 - Linux GCC/Clang
 > ⚠️ Apple Silicon (arm64) is not currently supported.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Run
### Launch Arguments
 - `--window` Launch in window mode
 - `--skip-intro` Launch skip intro animation and cover

## Known Issues
 - On windows platform, if the screen ratio is not set to 100%, it may cause window size problems. If you encounter this situation, it is recommended to use `--window` to run in windowed mode.
 - The sound may play 2 times per click, or not when clicked, which appears to be caused by the HTML renderer UltraLight, and we have not yet found a solution to this problem.
## Features
> ✋ Because of the limited time of the development team,  
>    we haven't finished all the features yet, we always welcome pull request or issue.  

|      | Name          | Description                                    |
| ---- | ------------- | ---------------------------------------------- |
| ✅    | Move Piece    | Move piece on the board                        |
| ✅    | Special Case  | Promoting/Castle/En Passant                    |
| ❎    | Undo/Redo     |                                                |
| ✅    | Show Result   | Win/Lose/Checkmate                             |
| ✅    | Menu          |                                                |
| ✅    | Resign        |                                                |
| ✅    | Timeout       | When the player's time is up, the player loses |
| ✅    | Display Clock | Display player's clock                         |
| ✅    | Who First     | Set custom first player in custom mode         |
| ❎    | FEN Standard  | Load custom game with FEN standard             |
| ❎    | Online Mode   | Multiplayer online games                       |

## Design
Beautiful and aesthetically pleasing user interface.  
All original materials are created by our designers.  
[Figma Design Project](https://www.figma.com/file/upeASWAWHpmBMB9tXlhOBT/chess-project?type=design&node-id=0%3A1&t=PiioRERyi1d0lOvg-1)
<img width="903" alt="截圖 2023-05-20 上午4 54 54" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/6253c40f-7c5e-4615-b05d-58a62cdabc3d">
<img width="1515" alt="截圖 2023-05-20 上午4 55 41" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/8acde07e-2fb6-46f7-bd43-70ac858a89a1">

### Assets Reference
| Type             | Name                      | Source                                                |
| ---------------- | ------------------------- | ----------------------------------------------------- |
| Background Music | Japanese Cute Vibes       | https://www.youtube.com/watch?v=nzO90ZYKUAQ           |
| Font             | Frostbite Boss Fight Font | https://fontmeme.com/fonts/frostbite-boss-fight-font/ |
