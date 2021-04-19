Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-fields", file = "./assets/tilemaps/fields.png"},
        [1] = { type="texture", id = "wildhammer", file = "./assets/images/wildhammer.png"},
        [2] = { type="texture", id = "catapult", file = "./assets/images/catapult-big-right.png"},
        [3] = { type="texture", id = "enemy-projectile", file = "./assets/images/enemy-projectile.png"},
        [4] = { type="font", id = "pixeldown", file = "./assets/fonts/pixeldown.png", fontSize = 14}
    },
    map = {
        textureAssetId = "terrain-fields",
        file = "./assets/tilemaps/fields.map",
        scale = 2,
        tilesize = 32,
        mapsizeX = 25,
        mapsizeY = 20
    },
    entities = {
        [0] = {
            name = "player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 240,
                        y = 106
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "wildhammer",
                    animated = true,
                    frameCount = 2,
                    animationSpeed = 90,
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
                        x = 650,
                        y = 405
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "catapult",
                    animated = false
                },
                collider = {
                    tag = "enemy"
                },
                projectileEmitter = {
                    textureAssetId = "enemy-projectile",
                    speed = 50,
                    range = 200,
                    angle = 180
                }
            }
        }
    }
}