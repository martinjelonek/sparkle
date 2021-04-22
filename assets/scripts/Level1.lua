Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-fields", file = "./assets/tilemaps/fields.png"},
        [1] = { type="texture", id = "wildhammer", file = "./assets/images/wildhammer.png"},
        [2] = { type="texture", id = "troops", file = "./assets/images/troops.png"},
        [3] = { type="texture", id = "troops-moveing", file = "./assets/images/troops-moveing.png"},
        [4] = { type="texture", id = "enemy-projectile", file = "./assets/images/enemy-projectile.png"},
        [5] = { type="font", id = "pixeldown", file = "./assets/fonts/pixeldown.ttf", fontSize = 14}
    },
    map = {
        textureAssetId = "terrain-fields",
        file = "./assets/tilemaps/fields.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
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
                }
            }
        },
        [1] = {
            name = "troops-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 192,
                        y = 160
                    },
                    velocity = {
                        x = 20,
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
                    hasDirection = false;
                    frameCount = 2,
                    animationSpeed = 375,
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
            name = "label-title",
            layer = 5,
            components = {
                label = {
                    x = 5,
                    y = 5,
                    text = "wildhammer",
                    fontFamily = "pixeldown",
                    color = "WHITE_COLOR"
                }
            }
        }
    }
}