xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 60;
 0.00000;-18.58206;-25.05794;,
 0.00000;0.38769;-66.13312;,
 12.90470;-13.23757;-24.96465;,
 0.00000;0.38769;-66.13312;,
 18.25000;-0.33484;-24.73942;,
 0.00000;0.38769;-66.13312;,
 12.90470;12.56789;-24.51421;,
 0.00000;0.38769;-66.13312;,
 -0.00000;17.91238;-24.42092;,
 0.00000;0.38769;-66.13312;,
 -12.90470;12.56789;-24.51421;,
 0.00000;0.38769;-66.13312;,
 -18.25000;-0.33484;-24.73942;,
 0.00000;0.38769;-66.13312;,
 -12.90470;-13.23757;-24.96465;,
 0.00000;0.38769;-66.13312;,
 0.00000;-18.58206;-25.05794;,
 0.00000;-0.33484;-24.73942;,
 0.00000;-18.58206;-25.05794;,
 12.90470;-13.23757;-24.96465;,
 18.25000;-0.33484;-24.73942;,
 12.90470;12.56789;-24.51421;,
 -0.00000;17.91238;-24.42092;,
 -12.90470;12.56789;-24.51421;,
 -18.25000;-0.33484;-24.73942;,
 -12.90470;-13.23757;-24.96465;,
 0.00000;5.86484;32.70244;,
 4.34871;4.06362;32.68672;,
 4.34871;4.63347;-32.61082;,
 0.00000;6.43469;-32.59509;,
 6.15000;-0.28492;32.64877;,
 6.15000;0.28492;-32.64877;,
 4.34871;-4.63347;32.61082;,
 4.34871;-4.06362;-32.68672;,
 -0.00000;-6.43469;32.59509;,
 -0.00000;-5.86484;-32.70244;,
 -4.34871;-4.63347;32.61082;,
 -4.34871;-4.06362;-32.68672;,
 -6.15000;-0.28492;32.64877;,
 -6.15000;0.28492;-32.64877;,
 -4.34871;4.06362;32.68672;,
 -4.34871;4.63347;-32.61082;,
 0.00000;5.86484;32.70244;,
 0.00000;6.43469;-32.59509;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;-0.28492;32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;,
 0.00000;0.28492;-32.64877;;
 
 40;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 3;44,27,26;,
 3;45,30,27;,
 3;46,32,30;,
 3;47,34,32;,
 3;48,36,34;,
 3;49,38,36;,
 3;50,40,38;,
 3;51,42,40;,
 3;52,29,28;,
 3;53,28,31;,
 3;54,31,33;,
 3;55,33,35;,
 3;56,35,37;,
 3;57,37,39;,
 3;58,39,41;,
 3;59,41,43;;
 
 MeshMaterialList {
  1;
  40;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.790400;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  41;
  0.000000;-0.907859;-0.419276;,
  0.647030;-0.639891;-0.414599;,
  0.915038;0.007040;-0.403307;,
  0.647029;0.653971;-0.392014;,
  -0.000000;0.921938;-0.387337;,
  -0.647030;0.653971;-0.392014;,
  -0.915038;0.007040;-0.403307;,
  -0.647030;-0.639891;-0.414599;,
  0.000000;-0.017453;0.999848;,
  -0.000000;-0.008727;0.999962;,
  0.000000;0.999962;0.008727;,
  0.707106;0.707080;0.006171;,
  1.000000;0.000000;0.000000;,
  0.707106;-0.707080;-0.006171;,
  0.000000;-0.999962;-0.008727;,
  -0.707107;-0.707080;-0.006171;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.707080;0.006171;,
  -0.000000;0.008727;-0.999962;,
  -0.000000;-0.017453;0.999848;,
  -0.000000;-0.017453;0.999848;,
  0.000000;-0.017452;0.999848;,
  0.000000;-0.017452;0.999848;,
  0.000000;-0.017452;0.999848;,
  -0.000000;-0.017452;0.999848;,
  0.000000;-0.017453;0.999848;,
  0.000000;-0.017453;0.999848;,
  -0.000000;-0.008728;0.999962;,
  -0.000000;-0.008728;0.999962;,
  0.000000;-0.008726;0.999962;,
  -0.000001;-0.008726;0.999962;,
  0.000000;-0.008727;0.999962;,
  0.000001;-0.008726;0.999962;,
  0.000000;-0.008728;0.999962;,
  -0.000000;0.008727;-0.999962;,
  -0.000001;0.008726;-0.999962;,
  0.000000;0.008726;-0.999962;,
  -0.000000;0.008728;-0.999962;,
  -0.000000;0.008728;-0.999962;,
  0.000000;0.008728;-0.999962;,
  0.000001;0.008726;-0.999962;;
  40;
  3;0,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,4;,
  3;4,5,5;,
  3;5,5,6;,
  3;6,7,7;,
  3;7,7,0;,
  3;8,19,20;,
  3;8,20,21;,
  3;8,21,22;,
  3;8,22,23;,
  3;8,23,24;,
  3;8,24,25;,
  3;8,25,26;,
  3;8,26,19;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,10,10,17;,
  3;9,27,28;,
  3;9,29,27;,
  3;9,30,29;,
  3;9,31,30;,
  3;9,32,31;,
  3;9,29,32;,
  3;9,33,29;,
  3;9,28,33;,
  3;18,34,35;,
  3;18,35,36;,
  3;18,36,37;,
  3;18,37,38;,
  3;18,38,39;,
  3;18,39,36;,
  3;18,36,40;,
  3;18,40,34;;
 }
 MeshTextureCoords {
  60;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
