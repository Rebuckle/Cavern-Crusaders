<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.2.3" name="ObstacleTiles" tilewidth="106" tileheight="106" tilecount="3" columns="3">
 <image source="../../../../TileMap_Images/ObstacleTiles.png" trans="ffffff" width="341" height="171"/>
 <tile id="0">
  <objectgroup draworder="index">
   <object id="2" name="SpikeDown" x="1" y="0">
    <polygon points="0,0 106,1 105,105 -3,56"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="1">
  <objectgroup draworder="index">
   <object id="1" name="SpikeDown" x="-2" y="0">
    <polygon points="0,0 66,0 8,106"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup draworder="index">
   <object id="1" name="SpikeUp" x="-2" y="105">
    <polygon points="0,0 8,-45 18,-4 26,-20 33,-5 39,-19 49,-7 62,-5 82,-66 94,-9 105,-16 107,-1"/>
   </object>
  </objectgroup>
 </tile>
</tileset>
