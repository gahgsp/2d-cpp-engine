Level1 = {
    assets = {
        [0] = { type="texture", id = "Jungle-Day", file = "../assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "Jungle-Night", file = "../assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "Chopper-Image", file = "../assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "Tank-Image", file = "../assets/images/tank-big-right.png" },
        [4] = { type="texture", id = "Enemy-Projectile", file = "../assets/images/bullet-enemy.png" },
        [5] = { type="texture", id = "Collider-Box", file = "../assets/images/collision-texture.png" },
        [6] = { type="font", id = "Charriot-Font", file = "../assets/fonts/charriot.ttf", fontSize = 14 }
    },
    map = {
        textureAssetId = "Jungle-Day",
        file = "../assets/tilemaps/jungle.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
    },
    entities = {
        [0] = {
            name = "Player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 240,
                        y = 106
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1
                },
                sprite = {
                    textureAssetId = "Chopper-Image",
                    animated = true,
                    frameCount = 2,
                    animationSpeed = 90,
                    hasDirections = true,
                    fixed = false
                },
                collider = {
                    tag = "Player"
                },
                input = {
                    keyboard = {
                        up = "up",
                        right = "right",
                        down = "down",
                        left = "left",
                        shoot = "space"
                    }
                }
            }
        },
        [1] = {
            name = "Enemy-Tank-1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 150,
                        y = 495
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1
                },
                sprite = {
                    textureAssetId = "Tank-Image",
                    animated = false
                },
                collider = {
                    tag = "Enemy"
                },
                projectileEmitter = {
                    textureAssetId = "Enemy-Projectile",
                    width = 4,
                    height = 4,
                    speed = 50,
                    angle = 270,
                    range = 200,
                    shouldLoop = true
                }
            }
        }
    }
}
