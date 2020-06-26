Level1 = {
    assets = {
        [0] = { type="texture", id = "Jungle-Day", file = "../assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "Jungle-Night", file = "../assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "Chopper-Image", file = "../assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "Tank-Image-Right", file = "../assets/images/tank-big-right.png" },
        [4] = { type="texture", id = "Tank-Image-Left", file = "../assets/images/tank-big-left.png" },
        [5] = { type="texture", id = "Tank-Image-Down", file = "../assets/images/tank-big-down.png" },
        [6] = { type="texture", id = "Enemy-Projectile", file = "../assets/images/bullet-enemy.png" },
        [7] = { type="texture", id = "Collider-Box", file = "../assets/images/collision-texture.png" },
        [8] = { type="texture", id = "Radar-Image", file = "../assets/images/radar.png" },
        [9] = { type="texture", id = "Start-Point", file = "../assets/images/start.png" },
        [10] = { type="texture", id = "End-Point", file = "../assets/images/heliport.png" },
        [11] = { type="font", id = "Charriot-Font", file = "../assets/fonts/charriot.ttf", fontSize = 14 }
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
                    textureAssetId = "Tank-Image-Right"
                },
                collider = {
                    tag = "Enemy"
                },
                projectileEmitter = {
                    textureAssetId = "Enemy-Projectile",
                    width = 4,
                    height = 4,
                    speed = 200,
                    angle = 0,
                    range = 300,
                    shouldLoop = true
                }
            }
        },
        [2] = {
            name = "Radar",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = 720,
                        y = 15
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 64,
                    height = 64,
                    scale = 1
                },
                sprite = {
                    textureAssetId = "Radar-Image",
                    animated = true,
                    frameCount = 8,
                    animationSpeed = 150,
                    hasDirections = false,
                    fixed = true
                }
            }
        },
        [3] = {
            name = "Level-Name",
            layer = 5,
            components = {
                label = {
                    position = {
                        x = 10,
                        y = 10
                    },
                    text = "First Level",
                    fontFamily = "Charriot-Font",
                    color = {
                        r = 255,
                        g = 255,
                        b = 255,
                        a = 255
                    }
                }
            }
        },
        [4] = {
            name = "Enemy-Tank-2",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 500,
                        y = 390
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
                    textureAssetId = "Tank-Image-Down"
                },
                collider = {
                    tag = "Enemy"
                },
                projectileEmitter = {
                    textureAssetId = "Enemy-Projectile",
                    width = 4,
                    height = 4,
                    speed = 200,
                    angle = 90,
                    range = 300,
                    shouldLoop = true
                }
            }
        },
        [5] = {
            name = "Enemy-Tank-3",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 220,
                        y = 1000
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
                    textureAssetId = "Tank-Image-Right"
                },
                collider = {
                    tag = "Enemy"
                },
                projectileEmitter = {
                    textureAssetId = "Enemy-Projectile",
                    width = 4,
                    height = 4,
                    speed = 200,
                    angle = 0,
                    range = 500,
                    shouldLoop = true
                }
            }
        },
        [6] = {
            name = "Enemy-Tank-4",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 700,
                        y = 800
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
                    textureAssetId = "Tank-Image-Left"
                },
                collider = {
                    tag = "Enemy"
                },
                projectileEmitter = {
                    textureAssetId = "Enemy-Projectile",
                    width = 4,
                    height = 4,
                    speed = 200,
                    angle = 180,
                    range = 300,
                    shouldLoop = true
                }
            }
        },
        [7] = {
            name = "Enemy-Tank-5",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 800,
                        y = 390
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
                    textureAssetId = "Tank-Image-Down"
                },
                collider = {
                    tag = "Enemy"
                },
                projectileEmitter = {
                    textureAssetId = "Enemy-Projectile",
                    width = 4,
                    height = 4,
                    speed = 200,
                    angle = 90,
                    range = 800,
                    shouldLoop = true
                }
            }
        },
        [8] = {
            name = "Ending-Point",
            layer = 0,
            components = {
                transform = {
                    position = {
                    x = 1420,
                    y = 784
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
                    textureAssetId = "End-Point"
                },
                collider = {
                    tag = "Level-Complete"
                }
            }
        }
    }
}
