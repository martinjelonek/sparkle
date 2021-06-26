-- WILDHAMMER - WIN

--Variable

--Data
Scene5 = {
    conf = {
        sceneWidth = 1280,
        sceneHeight = 720,
        lostScene = 4
    },
    control = {
        keyboard = {
            ----navigate between scenes
            --set scene number or NULL
            key1 = "NULL",
            key2 = "NULL",
            --set scene number, CLOSE for close the app or NULL
            keyEsc = "0",
            --set scene number or NULL
            keyEnter = "2"
        }
    },
    assets = {
        [0] = { type="font", id = "pixeldown7", file = "./assets/fonts/pixeldown.ttf", fontSize = 7},
        [1] = { type="font", id = "pixeldown19", file = "./assets/fonts/pixeldown.ttf", fontSize = 19},
        [2] = { type="font", id = "pixeldown39", file = "./assets/fonts/pixeldown.ttf", fontSize = 39},
    },
    entities = {
        [0] = {
            name = "title",
            layer = 5,
            components = {
                label = {
                    x = 480,
                    y = 200,
                    text = "you win!",
                    fontFamily = "pixeldown39",
                    color = "WHITE_COLOR"
                }
            }
        },
        [1] = {
            name = "label-restart",
            layer = 5,
            components = {
                label = {
                    x = 410,
                    y = 330,
                    text = "press enter to restart",
                    fontFamily = "pixeldown19",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [2] = {
            name = "label-exit",
            layer = 5,
            components = {
                label = {
                    x = 470,
                    y = 380,
                    text = "press esc to exit",
                    fontFamily = "pixeldown19",
                    color = "ORANGE_COLOR"
                }
            }
        }
    }
}