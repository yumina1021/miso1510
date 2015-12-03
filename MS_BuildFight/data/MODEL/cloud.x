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
 216;
 0.37993;58.95169;2.64422;,
 34.48907;31.10169;-1.90338;,
 0.37993;31.10169;-3.78706;,
 48.61755;31.10169;2.64422;,
 34.48907;31.10169;7.19182;,
 0.37993;31.10169;9.07550;,
 -33.72923;31.10169;7.19182;,
 -47.85769;31.10169;2.64422;,
 -33.72923;31.10169;-1.90338;,
 34.48907;-24.59831;-1.90338;,
 0.37993;-24.59831;-3.78706;,
 48.61754;-24.59831;2.64422;,
 34.48907;-24.59831;7.19182;,
 0.37993;-24.59831;9.07550;,
 -33.72922;-24.59831;7.19182;,
 -47.85769;-24.59831;2.64422;,
 -33.72922;-24.59831;-1.90338;,
 0.37993;-52.44831;2.64422;,
 -46.38060;141.98125;2.64423;,
 -12.27145;114.13124;-2.13594;,
 -46.38060;114.13124;-4.11594;,
 1.85702;114.13124;2.64423;,
 -12.27145;114.13124;7.42439;,
 -46.38060;114.13124;9.40439;,
 -80.48975;114.13124;7.42439;,
 -94.61821;114.13124;2.64423;,
 -80.48975;114.13124;-2.13593;,
 -12.27145;58.43124;-2.13593;,
 -46.38060;58.43124;-4.11594;,
 1.85702;58.43124;2.64423;,
 -12.27145;58.43124;7.42439;,
 -46.38060;58.43124;9.40439;,
 -80.48975;58.43124;7.42439;,
 -94.61821;58.43124;2.64423;,
 -80.48975;58.43124;-2.13593;,
 -46.38060;30.58124;2.64423;,
 96.04097;58.79331;2.64423;,
 130.15012;30.94331;-1.76930;,
 96.04097;30.94331;-3.59744;,
 144.27859;30.94331;2.64423;,
 130.15012;30.94331;7.05775;,
 96.04096;30.94331;8.88589;,
 61.93182;30.94331;7.05775;,
 47.80335;30.94331;2.64423;,
 61.93182;30.94331;-1.76930;,
 130.15012;-24.75669;-1.76930;,
 96.04097;-24.75669;-3.59744;,
 144.27858;-24.75669;2.64423;,
 130.15012;-24.75669;7.05775;,
 96.04096;-24.75669;8.88589;,
 61.93182;-24.75669;7.05775;,
 47.80336;-24.75669;2.64423;,
 61.93182;-24.75669;-1.76930;,
 96.04097;-52.60669;2.64423;,
 193.03369;58.79331;2.64423;,
 227.14284;30.94331;-2.61108;,
 193.03369;30.94331;-4.78790;,
 241.27130;30.94331;2.64423;,
 227.14284;30.94331;7.89953;,
 193.03369;30.94331;10.07635;,
 158.92453;30.94331;7.89953;,
 144.79608;30.94331;2.64423;,
 158.92453;30.94331;-2.61108;,
 227.14284;-24.75669;-2.61108;,
 193.03369;-24.75669;-4.78790;,
 241.27130;-24.75669;2.64423;,
 227.14284;-24.75669;7.89953;,
 193.03369;-24.75669;10.07634;,
 158.92455;-24.75669;7.89953;,
 144.79608;-24.75669;2.64423;,
 158.92455;-24.75669;-2.61108;,
 193.03369;-52.60669;2.64423;,
 146.19283;-24.51333;2.64423;,
 180.30197;-52.36333;-1.49221;,
 146.19283;-52.36333;-3.20558;,
 194.43045;-52.36333;2.64423;,
 180.30197;-52.36333;6.78067;,
 146.19283;-52.36333;8.49403;,
 112.08367;-52.36333;6.78066;,
 97.95521;-52.36333;2.64423;,
 112.08367;-52.36333;-1.49221;,
 180.30197;-108.06334;-1.49221;,
 146.19283;-108.06334;-3.20558;,
 194.43044;-108.06334;2.64423;,
 180.30197;-108.06334;6.78067;,
 146.19283;-108.06334;8.49403;,
 112.08368;-108.06334;6.78066;,
 97.95522;-108.06334;2.64423;,
 112.08368;-108.06334;-1.49221;,
 146.19283;-135.91333;2.64423;,
 242.35641;-24.51333;2.64423;,
 276.46558;-52.36333;-2.25664;,
 242.35641;-52.36333;-4.28664;,
 290.59402;-52.36333;2.64423;,
 276.46558;-52.36333;7.54509;,
 242.35641;-52.36333;9.57510;,
 208.24725;-52.36333;7.54509;,
 194.11880;-52.36333;2.64423;,
 208.24725;-52.36333;-2.25664;,
 276.46558;-108.06334;-2.25664;,
 242.35641;-108.06334;-4.28664;,
 290.59402;-108.06334;2.64423;,
 276.46555;-108.06334;7.54509;,
 242.35641;-108.06334;9.57510;,
 208.24727;-108.06334;7.54509;,
 194.11880;-108.06334;2.64423;,
 208.24727;-108.06334;-2.25664;,
 242.35641;-135.91333;2.64423;,
 287.61060;-110.14589;2.64423;,
 321.71973;-137.99588;-1.79137;,
 287.61060;-137.99588;-3.62865;,
 335.84821;-137.99588;2.64423;,
 321.71973;-137.99588;7.07982;,
 287.61060;-137.99588;8.91710;,
 253.50143;-137.99588;7.07982;,
 239.37299;-137.99588;2.64423;,
 253.50143;-137.99588;-1.79137;,
 321.71973;-193.69589;-1.79137;,
 287.61060;-193.69589;-3.62865;,
 335.84821;-193.69589;2.64423;,
 321.71973;-193.69589;7.07982;,
 287.61060;-193.69589;8.91710;,
 253.50145;-193.69589;7.07982;,
 239.37299;-193.69589;2.64423;,
 253.50145;-193.69589;-1.79136;,
 287.61060;-221.54588;2.64423;,
 -51.32522;-24.52461;2.64423;,
 -17.21607;-52.37461;-5.34577;,
 -51.32522;-52.37461;-8.65533;,
 -3.08760;-52.37461;2.64423;,
 -17.21607;-52.37461;10.63423;,
 -51.32522;-52.37461;13.94379;,
 -85.43437;-52.37461;10.63422;,
 -99.56284;-52.37461;2.64423;,
 -85.43437;-52.37461;-5.34577;,
 -17.21607;-108.07462;-5.34577;,
 -51.32522;-108.07462;-8.65533;,
 -3.08760;-108.07462;2.64423;,
 -17.21608;-108.07462;10.63423;,
 -51.32522;-108.07462;13.94379;,
 -85.43437;-108.07462;10.63422;,
 -99.56284;-108.07462;2.64423;,
 -85.43437;-108.07462;-5.34577;,
 -51.32522;-135.92461;2.64423;,
 48.92437;-24.52461;2.64423;,
 83.03352;-52.37461;-4.20118;,
 48.92437;-52.37461;-7.03663;,
 97.16199;-52.37461;2.64423;,
 83.03352;-52.37461;9.48962;,
 48.92437;-52.37461;12.32508;,
 14.81522;-52.37461;9.48962;,
 0.68675;-52.37461;2.64423;,
 14.81522;-52.37461;-4.20118;,
 83.03352;-108.07462;-4.20118;,
 48.92437;-108.07462;-7.03663;,
 97.16199;-108.07462;2.64423;,
 83.03351;-108.07462;9.48962;,
 48.92437;-108.07462;12.32508;,
 14.81522;-108.07462;9.48962;,
 0.68676;-108.07462;2.64423;,
 14.81522;-108.07462;-4.20118;,
 48.92437;-135.92461;2.64423;,
 -96.14233;59.70747;2.64423;,
 -62.03319;31.85746;-4.76983;,
 -96.14233;31.85746;-7.84084;,
 -47.90472;31.85746;2.64423;,
 -62.03319;31.85746;10.05829;,
 -96.14234;31.85746;13.12929;,
 -130.25150;31.85746;10.05828;,
 -144.37994;31.85746;2.64423;,
 -130.25150;31.85746;-4.76983;,
 -62.03319;-23.84254;-4.76983;,
 -96.14233;-23.84254;-7.84084;,
 -47.90472;-23.84254;2.64423;,
 -62.03319;-23.84254;10.05829;,
 -96.14234;-23.84254;13.12929;,
 -130.25148;-23.84254;10.05828;,
 -144.37994;-23.84254;2.64423;,
 -130.25148;-23.84254;-4.76983;,
 -96.14233;-51.69254;2.64423;,
 -143.69128;146.53296;2.64423;,
 -109.58214;118.68296;-3.19137;,
 -143.69128;118.68296;-5.60855;,
 -95.45367;118.68296;2.64423;,
 -109.58214;118.68296;8.47981;,
 -143.69128;118.68296;10.89699;,
 -177.80045;118.68296;8.47981;,
 -191.92889;118.68296;2.64423;,
 -177.80045;118.68296;-3.19137;,
 -109.58214;62.98296;-3.19137;,
 -143.69128;62.98296;-5.60855;,
 -95.45367;62.98296;2.64423;,
 -109.58214;62.98296;8.47981;,
 -143.69128;62.98296;10.89699;,
 -177.80043;62.98296;8.47981;,
 -191.92889;62.98296;2.64423;,
 -177.80043;62.98296;-3.19137;,
 -143.69128;35.13296;2.64423;,
 -93.38305;227.97867;2.64423;,
 -59.27390;200.12866;-3.61340;,
 -93.38305;200.12866;-6.20540;,
 -45.14543;200.12866;2.64423;,
 -59.27390;200.12866;8.90186;,
 -93.38306;200.12866;11.49386;,
 -127.49220;200.12866;8.90186;,
 -141.62067;200.12866;2.64423;,
 -127.49220;200.12866;-3.61340;,
 -59.27390;144.42867;-3.61340;,
 -93.38305;144.42867;-6.20540;,
 -45.14544;144.42867;2.64423;,
 -59.27391;144.42867;8.90186;,
 -93.38306;144.42867;11.49386;,
 -127.49220;144.42867;8.90186;,
 -141.62067;144.42867;2.64423;,
 -127.49220;144.42867;-3.61340;,
 -93.38305;116.57867;2.64423;;
 
 288;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 3;10,9,17;,
 3;9,11,17;,
 3;11,12,17;,
 3;12,13,17;,
 3;13,14,17;,
 3;14,15,17;,
 3;15,16,17;,
 3;16,10,17;,
 3;18,19,20;,
 3;18,21,19;,
 3;18,22,21;,
 3;18,23,22;,
 3;18,24,23;,
 3;18,25,24;,
 3;18,26,25;,
 3;18,20,26;,
 4;20,19,27,28;,
 4;19,21,29,27;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,25,33,32;,
 4;25,26,34,33;,
 4;26,20,28,34;,
 3;28,27,35;,
 3;27,29,35;,
 3;29,30,35;,
 3;30,31,35;,
 3;31,32,35;,
 3;32,33,35;,
 3;33,34,35;,
 3;34,28,35;,
 3;36,37,38;,
 3;36,39,37;,
 3;36,40,39;,
 3;36,41,40;,
 3;36,42,41;,
 3;36,43,42;,
 3;36,44,43;,
 3;36,38,44;,
 4;38,37,45,46;,
 4;37,39,47,45;,
 4;39,40,48,47;,
 4;40,41,49,48;,
 4;41,42,50,49;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,38,46,52;,
 3;46,45,53;,
 3;45,47,53;,
 3;47,48,53;,
 3;48,49,53;,
 3;49,50,53;,
 3;50,51,53;,
 3;51,52,53;,
 3;52,46,53;,
 3;54,55,56;,
 3;54,57,55;,
 3;54,58,57;,
 3;54,59,58;,
 3;54,60,59;,
 3;54,61,60;,
 3;54,62,61;,
 3;54,56,62;,
 4;56,55,63,64;,
 4;55,57,65,63;,
 4;57,58,66,65;,
 4;58,59,67,66;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,56,64,70;,
 3;64,63,71;,
 3;63,65,71;,
 3;65,66,71;,
 3;66,67,71;,
 3;67,68,71;,
 3;68,69,71;,
 3;69,70,71;,
 3;70,64,71;,
 3;72,73,74;,
 3;72,75,73;,
 3;72,76,75;,
 3;72,77,76;,
 3;72,78,77;,
 3;72,79,78;,
 3;72,80,79;,
 3;72,74,80;,
 4;74,73,81,82;,
 4;73,75,83,81;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,74,82,88;,
 3;82,81,89;,
 3;81,83,89;,
 3;83,84,89;,
 3;84,85,89;,
 3;85,86,89;,
 3;86,87,89;,
 3;87,88,89;,
 3;88,82,89;,
 3;90,91,92;,
 3;90,93,91;,
 3;90,94,93;,
 3;90,95,94;,
 3;90,96,95;,
 3;90,97,96;,
 3;90,98,97;,
 3;90,92,98;,
 4;92,91,99,100;,
 4;91,93,101,99;,
 4;93,94,102,101;,
 4;94,95,103,102;,
 4;95,96,104,103;,
 4;96,97,105,104;,
 4;97,98,106,105;,
 4;98,92,100,106;,
 3;100,99,107;,
 3;99,101,107;,
 3;101,102,107;,
 3;102,103,107;,
 3;103,104,107;,
 3;104,105,107;,
 3;105,106,107;,
 3;106,100,107;,
 3;108,109,110;,
 3;108,111,109;,
 3;108,112,111;,
 3;108,113,112;,
 3;108,114,113;,
 3;108,115,114;,
 3;108,116,115;,
 3;108,110,116;,
 4;110,109,117,118;,
 4;109,111,119,117;,
 4;111,112,120,119;,
 4;112,113,121,120;,
 4;113,114,122,121;,
 4;114,115,123,122;,
 4;115,116,124,123;,
 4;116,110,118,124;,
 3;118,117,125;,
 3;117,119,125;,
 3;119,120,125;,
 3;120,121,125;,
 3;121,122,125;,
 3;122,123,125;,
 3;123,124,125;,
 3;124,118,125;,
 3;126,127,128;,
 3;126,129,127;,
 3;126,130,129;,
 3;126,131,130;,
 3;126,132,131;,
 3;126,133,132;,
 3;126,134,133;,
 3;126,128,134;,
 4;128,127,135,136;,
 4;127,129,137,135;,
 4;129,130,138,137;,
 4;130,131,139,138;,
 4;131,132,140,139;,
 4;132,133,141,140;,
 4;133,134,142,141;,
 4;134,128,136,142;,
 3;136,135,143;,
 3;135,137,143;,
 3;137,138,143;,
 3;138,139,143;,
 3;139,140,143;,
 3;140,141,143;,
 3;141,142,143;,
 3;142,136,143;,
 3;144,145,146;,
 3;144,147,145;,
 3;144,148,147;,
 3;144,149,148;,
 3;144,150,149;,
 3;144,151,150;,
 3;144,152,151;,
 3;144,146,152;,
 4;146,145,153,154;,
 4;145,147,155,153;,
 4;147,148,156,155;,
 4;148,149,157,156;,
 4;149,150,158,157;,
 4;150,151,159,158;,
 4;151,152,160,159;,
 4;152,146,154,160;,
 3;154,153,161;,
 3;153,155,161;,
 3;155,156,161;,
 3;156,157,161;,
 3;157,158,161;,
 3;158,159,161;,
 3;159,160,161;,
 3;160,154,161;,
 3;162,163,164;,
 3;162,165,163;,
 3;162,166,165;,
 3;162,167,166;,
 3;162,168,167;,
 3;162,169,168;,
 3;162,170,169;,
 3;162,164,170;,
 4;164,163,171,172;,
 4;163,165,173,171;,
 4;165,166,174,173;,
 4;166,167,175,174;,
 4;167,168,176,175;,
 4;168,169,177,176;,
 4;169,170,178,177;,
 4;170,164,172,178;,
 3;172,171,179;,
 3;171,173,179;,
 3;173,174,179;,
 3;174,175,179;,
 3;175,176,179;,
 3;176,177,179;,
 3;177,178,179;,
 3;178,172,179;,
 3;180,181,182;,
 3;180,183,181;,
 3;180,184,183;,
 3;180,185,184;,
 3;180,186,185;,
 3;180,187,186;,
 3;180,188,187;,
 3;180,182,188;,
 4;182,181,189,190;,
 4;181,183,191,189;,
 4;183,184,192,191;,
 4;184,185,193,192;,
 4;185,186,194,193;,
 4;186,187,195,194;,
 4;187,188,196,195;,
 4;188,182,190,196;,
 3;190,189,197;,
 3;189,191,197;,
 3;191,192,197;,
 3;192,193,197;,
 3;193,194,197;,
 3;194,195,197;,
 3;195,196,197;,
 3;196,190,197;,
 3;198,199,200;,
 3;198,201,199;,
 3;198,202,201;,
 3;198,203,202;,
 3;198,204,203;,
 3;198,205,204;,
 3;198,206,205;,
 3;198,200,206;,
 4;200,199,207,208;,
 4;199,201,209,207;,
 4;201,202,210,209;,
 4;202,203,211,210;,
 4;203,204,212,211;,
 4;204,205,213,212;,
 4;205,206,214,213;,
 4;206,200,208,214;,
 3;208,207,215;,
 3;207,209,215;,
 3;209,210,215;,
 3;210,211,215;,
 3;211,212,215;,
 3;212,213,215;,
 3;213,214,215;,
 3;214,208,215;;
 
 MeshMaterialList {
  1;
  288;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}