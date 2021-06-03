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
        [3] = { type="texture", id = "terrain-fields", file = "./assets/tilemaps/fields.png"},
        [4] = { type="texture", id = "key-plus", file = "./assets/images/key-plus.png"},
        [5] = { type="texture", id = "key-minus", file = "./assets/images/key-minus.png"}
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
                    fixed = true
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
            name = "info-row-3",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 250,
                    text = "W, S, A, D - move view",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [8] = {
            name = "info-row-4",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 280,
                    text = "Esc - back to menu",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [9] = {
            name = "info-row-5",
            layer = 3,
            components = {
                label = {
                    x = 5,
                    y = 310,
                    text = "Q - save map",
                    fontFamily = "pixeldown7",
                    color = "ORANGE_COLOR"
                }
            }
        },
        [10] = {
            name = "map-editor",
            layer = 3,
            components = {
                mapeditor = {
                    labelNameX = "map-size-text-x",
                    labelNameY = "map-size-text-y",
                    mapSizeX = 20,
                    mapSizeY = 20,
                    fontFamily = "pixeldown7",
                    mapTextureId = "terrain-fields",
                    mapScale = 1,
                    mapTileSize = 32,
                    mapDefaultPositionX = -331,
                    mapDefaultPositionY = -31,
                }
            }
        },
        [11] = {
            name = "key-plus-x",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 150,
                        y = 38
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 0.5,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-plus",
                    animated = false,
                    fixed = true
                }
            }
        },
        [12] = {
            name = "key-minus-x",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 168,
                        y = 38
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 0.5,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-minus",
                    animated = false,
                    fixed = true
                }
            }
        },
        [13] = {
            name = "key-plus-y",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 150,
                        y = 68
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 0.5,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-plus",
                    animated = false,
                    fixed = true
                }
            }
        },
        [14] = {
            name = "key-minus-y",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 168,
                        y = 68
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 0.5,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "key-minus",
                    animated = false,
                    fixed = true
                }
            }
        },
        [15] = {
            name = "line-bg",
            layer = 1,
            components = {
                rectangle = {
                    x = 0,
                    y = 30,
                    w = 330,
                    h = 1,
                    r = 0,
                    g = 0,
                    b = 0
                }
            }
        }
    }
}