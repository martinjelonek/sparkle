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
        [3] = { type="texture", id = "terrain-fields", file = "./assets/tilemaps/fields.png"}
    },
    entities = {
        [0] = {
            name = "title-bg",
            layer = 2,
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
            layer = 3,
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
            layer = 2,
            components = {
                rectangle = {
                    x = 0,
                    y = 31,
                    w = 330,
                    h = 690,
                    r = 120,
                    g = 120,
                    b = 120
                }
            }
        },
        [3] = {
            name = "map-size-text-x",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 35,
                    text = "map size x:",
                    fontFamily = "pixeldown7",
                    color = "WHITE_COLOR"
                }
            }
        },
        [4] = {
            name = "map-size-text-y",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 60,
                    text = "map size y:",
                    fontFamily = "pixeldown7",
                    color = "WHITE_COLOR"
                }
            }
        },
        [5] = {
            name = "tilemap",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 5,
                        y = 90
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 320,
                    height = 96,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "terrain-fields",
                    animated = false,
                    fixed = false
                }
            }
        },
        [6] = {
            name = "info-row-1",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 220,
                    text = "LMB - choose / set tile",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [7] = {
            name = "info-row-2",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 250,
                    text = "RMB - set first tile",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [8] = {
            name = "info-row-3",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 280,
                    text = "W, S, A, D - move view",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [9] = {
            name = "info-row-4",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 310,
                    text = "Esc - back to menu",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [10] = {
            name = "info-row-5",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 340,
                    text = "Enter - save map",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        }
    }
}