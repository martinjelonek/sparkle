-- MAIN MANU

--Variable
KeyTextSpace = 60

MarginTitleX = 400
MarginTitleY = 50
MarginSubtitleX = 375
MarginSubtitleY = MarginTitleY + 94
MarginFirstLineX = 375
MarginFirstLineY = MarginSubtitleY + 94
MarginSecondLineX = 375
MarginSecondLineY = MarginFirstLineY + 55
MarginThirdLineX = 375
MarginThirdLineY = MarginSecondLineY + 55
BottomLineX = 550
BottomLineY = 690

--Data
Scene0 = {
    conf = {
        sceneWidth = 1600,
        sceneHeight = 1280
    },
    control = {
        keyboard = {
            ----navigate between scenes
            --set scene number or NULL
            key1 = "2",
            key2 = "6",
            --set scene number, CLOSE for close the app or NULL
            keyEsc = "CLOSE",
            --set scene number or NULL
            keyEnter = "NULL"
        }
    },
    assets = {
        [0] = { type="font", id = "pixeldown7", file = "./assets/fonts/pixeldown.ttf", fontSize = 7},
        [1] = { type="font", id = "pixeldown19", file = "./assets/fonts/pixeldown.ttf", fontSize = 19},
        [2] = { type="font", id = "pixeldown39", file = "./assets/fonts/pixeldown.ttf", fontSize = 39},
        [3] = { type="texture", id = "logo", file = "./assets/images/logo.png"},
        [4] = { type="texture", id = "key-1", file = "./assets/images/key-1.png"},
        [5] = { type="texture", id = "key-2", file = "./assets/images/key-2.png"},
        [6] = { type="texture", id = "key-esc", file = "./assets/images/key-esc.png"}
    },
    entities = {
        [0] = {
            name = "logo",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = MarginTitleX,
                        y = MarginTitleY
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 64,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "logo",
                    animated = false,
                    fixed = true
                }
           }
        },
        [1] = {
            name = "title",
            layer = 5,
            components = {
                label = {
                    x = MarginTitleX + 64 + 15,
                    y = MarginTitleY - 24,
                    text = "sparkle",
                    fontFamily = "pixeldown39",
                    color = "WHITE_COLOR"
                }
            }
        },
        [2] = {
            name = "subtitle",
            layer = 5,
            components = {
                label = {
                    x = MarginSubtitleX + 64 + 15,
                    y = MarginSubtitleY - 24,
                    text = "The 2D Game Engine",
                    fontFamily = "pixeldown19",
                    color = "WHITE_COLOR"
                }
            }
        },
        [3] = {
            name = "key-1",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = MarginFirstLineX,
                        y = MarginFirstLineY
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-1",
                    animated = false,
                    fixed = true
                }
           }
        },
        [4] = {
            name = "text-first-line",
            layer = 5,
            components = {
                label = {
                    x = MarginFirstLineX + KeyTextSpace,
                    y = MarginFirstLineY - 12,
                    text = "wildhammer game",
                    fontFamily = "pixeldown19",
                    color = "WHITE_COLOR"
                }
            }
        },
        [5] = {
            name = "key-2",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = MarginSecondLineX,
                        y = MarginSecondLineY
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-2",
                    animated = false,
                    fixed = true
                }
           }
        },
        [6] = {
            name = "text-first-line",
            layer = 5,
            components = {
                label = {
                    x = MarginSecondLineX + KeyTextSpace,
                    y = MarginSecondLineY - 12,
                    text = "map editor",
                    fontFamily = "pixeldown19",
                    color = "WHITE_COLOR"
                }
            }
        },
        [7] = {
            name = "key-esc",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = MarginThirdLineX,
                        y = MarginThirdLineY
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 50,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-esc",
                    animated = false,
                    fixed = true
                }
           }
        },
        [8] = {
            name = "text-third-line",
            layer = 5,
            components = {
                label = {
                    x = MarginThirdLineX + KeyTextSpace,
                    y = MarginThirdLineY - 12,
                    text = "quit",
                    fontFamily = "pixeldown19",
                    color = "WHITE_COLOR"
                }
            }
        },
        [9] = {
            name = "bottom-line",
            layer = 5,
            components = {
                label = {
                    x = BottomLineX,
                    y = BottomLineY,
                    text = "martin jelonek - 2021",
                    fontFamily = "pixeldown7",
                    color = "WHITE_COLOR"
                }
            }
        }
    }
}