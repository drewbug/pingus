;; generated by xml2sexpr.rb from file 'branches/pingus_0_6/data/levels/wip/jungle2.pingus'
(pingus-level 
  (version 2)
  (head 
    (levelname "The jungle / have fun part two")
    (description "You should have hired tarzus, not pingus : )")
    (author "Michael Mestre <mmestre@teaser.fr>")
    (number-of-pingus 50)
    (number-to-save 30)
    (time 5000)
    (actions 
      (basher 10)
      (blocker 10)
      (bomber 10)
      (bridger 15)
      (climber 10)
      (digger 10)
      (floater 10)
      (miner 10))
    (music "none")
    (levelsize 1600 864))
  (objects 
    (surface-background 
      (surface 
        (image "textures/nightjungle")
        (modifier "ROT0"))
      (color 1 1 1 0.2)
      (scroll-x 0.0)
      (scroll-y 0.0)
      (para-x 0.5)
      (para-y 0.5)
      (stretch-x 0)
      (stretch-y 0))
    (laser_exit 
      (position 896 122 -100))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/jungle/branch1")
        (modifier "ROT0"))
      (position 136 235 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/jungle/branch1")
        (modifier "ROT0"))
      (position 235 234 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/jungle/branch1")
        (modifier "ROT0"))
      (position 657 334 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/jungle/branch1")
        (modifier "ROT0"))
      (position 966 385 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/jungle/branch2")
        (modifier "ROT0"))
      (position 705 156 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/misc/stone0")
        (modifier "ROT0"))
      (position 885 253 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/misc/stone2")
        (modifier "ROT0"))
      (position 202 194 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/misc/column")
        (modifier "ROT0"))
      (position 1305 325 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/misc/column")
        (modifier "ROT0"))
      (position 1305 509 0))
    (groundpiece 
      (type "ground")
      (surface 
        (image "groundpieces/ground/misc/column")
        (modifier "ROT0"))
      (position 1305 693 0))
    (entrance 
      (position 328 158 0)
      (type "woodthing")
      (direction "left")
      (release-rate 40))
    (exit 
      (owner-id 0)
      (position 1375 325 0)
      (surface 
        (image "exits/stone")
        (modifier "ROT0")))
    (hotspot 
      (surface 
        (image "entrances/woodthing_nmov")
        (modifier "ROT0"))
      (position 252 23 100)
      (speed -1)
      (parallax 1))))
;; EOF ;;