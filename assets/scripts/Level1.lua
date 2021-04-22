Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-fields", file = "./assets/tilemaps/fields.png"},
        [1] = { type="texture", id = "wildhammer", file = "./assets/images/wildhammer.png"},
        [2] = { type="texture", id = "catapult", file = "./assets/images/catapult-big-right.png"},
        [3] = { type="texture", id = "enemy-projectile", file = "./assets/images/enemy-projectile.png"},
        [4] = { type="font", id = "pixeldown", file = "./assets/fonts/pixeldown.ttf", fontSize = 14}
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
                        x = 150,
                        y = 150
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
            name = "catapult-enemy-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 200,
                        y = 200
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
                    textureAssetId = "catapult",
                    animated = false,
                    fixed = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    width = 4,
                    height = 4,
                    speed = 50,
                    range = 200,
                    angle = 275,
                    loop = true
                }
            }
        },
        [2] = {
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