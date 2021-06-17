-- WILDAMMER - LEVEL 1

Scene2 = {
    conf = {
        sceneWidth = 1600,
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
            keyEnter = "3"
        }
    },
    map = {
        textureAssetId = "terrain-fields",
        file = "./assets/tilemaps/level1.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 20,
        mapSizeY = 40
    },
    entities = {
        [0] = {
            name = "player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 128,
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
                    sceneToLoad = 3
                }
            }
        },
        [1] = {
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
        [2] = {
            name = "troops-enemy-2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 192,
                        y = 192
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
            name = "ship-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 350,
                        y = 410
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
        [4] = {
            name = "tower-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 450,
                        y = 450
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tower",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 700,
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
                    angle = 180,
                    loop = true
                }
            }
        },
        [5] = {
            name = "label-title",
            layer = 5,
            components = {
                label = {
                    x = 5,
                    y = 5,
                    text = "wildhammer - level 1",
                    fontFamily = "pixeldown",
                    color = "WHITE_COLOR"
                }
            }
        },
        [6] = {
            name = "troops-enemy-3",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 320,
                        y = 192
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
                    angle = 100,
                    loop = true
                }
            }
        },
        [7] = {
            name = "troops-enemy-4",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 415,
                        y = 41
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
                    angle = 76,
                    loop = true
                }
            }
        },
        [8] = {
            name = "ship-enemy-2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 350,
                        y = 650
                    },
                    velocity = {
                        x = 20,
                        y = 1,
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
        [9] = {
            name = "tower-enemy-2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 1060,
                        y = 350
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tower",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 700,
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
                    angle = 135,
                    loop = true
                }
            }
        },
        [10] = {
            name = "tower-enemy-3",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 1060,
                        y = 200
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tower",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 700,
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
                    angle = 225,
                    loop = true
                }
            }
        },
        [11] = {
            name = "tower-enemy-4",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 1210,
                        y = 200
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tower",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 700,
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
        [12] = {
            name = "tower-enemy-5",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 1210,
                        y = 350
                    },
                    velocity = {
                        x = 0,
                        y = 0,
                    },
                    width = 32,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tower",
                    animated = true,
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 700,
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
                    angle = 45,
                    loop = true
                }
            }
        }
    }
}