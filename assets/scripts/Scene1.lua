-- WILDHAMMER INFO

--Variable

--Data
Scene1 = {
    conf = {
        sceneWidth = 2560,
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
                    x = 200,
                    y = 50,
                    text = "avoid enemys and reach right site of the map",
                    fontFamily = "pixeldown19",
                    color = "WHITE_COLOR"
                }
            }
        },
        [1] = {
            name = "title",
            layer = 5,
            components = {
                label = {
                    x = 450,
                    y = 200,
                    text = "move keys: WSAD",
                    fontFamily = "pixeldown19",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [2] = {
            name = "title",
            layer = 5,
            components = {
                label = {
                    x = 400,
                    y = 275,
                    text = "press enter to start",
                    fontFamily = "pixeldown19",
                    color = "ORANGE_COLOR"
                }
            }
        },
    }
}