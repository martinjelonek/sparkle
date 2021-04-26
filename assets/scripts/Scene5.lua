-- WILDHAMMER - WIN

--Variable

--Data
Scene5 = {
    conf = {
        sceneWidth = 1600,
        sceneHeight = 1280
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
            keyEnter = "NULL"
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
                    x = 50,
                    y = 50,
                    text = "wildhammer - win",
                    fontFamily = "pixeldown39",
                    color = "WHITE_COLOR"
                }
            }
        }
    }
}