-- WILDHAMMER - LEVEL 2

--Variable

--Data
Scene3 = {
    conf = {
        sceneWidth = 1280,
        sceneHeight = 1280,
        lostScene = 4
    },
    assets = {
        [0] = { type="texture", id = "terrain-fields", file = "./assets/tilemaps/fields.png"},
        [1] = { type="texture", id = "wildhammer", file = "./assets/images/wildhammer.png"},
        [2] = { type="texture", id = "troops", file = "./assets/images/troops.png"},
        [3] = { type="texture", id = "troops-moveing", file = "./assets/images/troops-moveing.png"},
        [4] = { type="texture", id = "enemy-projectile", file = "./assets/images/enemy-projectile.png"},
        [5] = { type="texture", id = "ship", file = "./assets/images/ship.png"},
        [6] = { type="texture", id = "tower", file = "./assets/images/tower.png"},
        [7] = { type="font", id = "pixeldown", file = "./assets/fonts/pixeldown.ttf", fontSize = 14}
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
    map = {
        textureAssetId = "terrain-fields",
        file = "./assets/tilemaps/level2.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 20,
        mapSizeY = 20
    },
    entities = {
        [0] = {
            name = "label-title",
            layer = 5,
            components = {
                label = {
                    x = 5,
                    y = 5,
                    text = "wildhammer - level 2",
                    fontFamily = "pixeldown",
                    color = "WHITE_COLOR"
                }
            }
        },
        [1] = {
            name = "player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 0,
                        y = 64
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "wildhammer",
                    animated = true,
                    hasDirection = true;
                    frameCount = 2,
                    animationSpeed = 375,
                    fixed = false
                },
                collider = {
                    tag = "player"
                },
                input = {
                    keyboard = {
                        up = "w",
                        left = "a",
                        down = "s",
                        right = "d",
                        shoot = "space"
                    }
                },
                triggerWin = {
                    sceneToLoad = 5
                }
            }
        },
        [2] = {
            name = "troops-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 36,
                        y = 160
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "troops",
                    animated = false,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 20,
                    height = 20,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        },
        [3] = {
            name = "troops-enemy-2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 130,
                        y = 250
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "troops",
                    animated = false,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 20,
                    height = 20,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        },
        [4] = {
            name = "troops-enemy-3",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 160,
                        y = 280
                    },
                    velocity = {
                        x = 10,
                        y = 0,
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "troops-moveing",
                    animated = true,
                    hasDirection = false,
                    frameCount = 2,
                    animationSpeed = 1000,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 20,
                    height = 20,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        },
        [5] = {
            name = "troops-enemy-4",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 1000,
                        y = 300
                    },
                    velocity = {
                        x = -10,
                        y = -2,
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "troops-moveing",
                    animated = true,
                    hasDirection = false,
                    frameCount = 2,
                    animationSpeed = 1000,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 20,
                    height = 20,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        },
        [6] = {
            name = "ship-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 350,
                        y = 460
                    },
                    velocity = {
                        x = 10,
                        y = 0,
                    },
                    width = 96,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "ship",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 1000,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 20,
                    height = 20,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        },
        [7] = {
            name = "ship-enemy-2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 280,
                        y = 500
                    },
                    velocity = {
                        x = 10,
                        y = 10,
                    },
                    width = 96,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "ship",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 1000,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 20,
                    height = 20,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        }
    }
}