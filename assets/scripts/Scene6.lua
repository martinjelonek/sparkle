-- MAP EDITOR

--Variable

--Data
Scene6 = {
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
            name = "title-bg",
            layer = 4,
            components = {
                rectangle = {
                    x = 0,
                    y = 0,
                    w = 1280,
                    h = 30,
                    r = 100,
                    g = 100,
                    b = 100
                }
            }
        },
        [1] = {
            name = "title",
            layer = 5,
            components = {
                label = {
                    x = 5,
                    y = 5,
                    text = "map editor",
                    fontFamily = "pixeldown7",
                    color = "WHITE_COLOR"
                }
            }
        },
        [2] = {
            name = "left-banner",
            layer = 4,
            components = {
                rectangle = {
                    x = 0,
                    y = 31,
                    w = 300,
                    h = 690,
                    r = 120,
                    g = 120,
                    b = 120
                }
            }
        }
    }
}