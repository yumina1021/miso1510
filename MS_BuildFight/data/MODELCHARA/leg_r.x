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
 269;
 -1.91300;-1.20740;-1.86470;,
 -1.91300;-0.75810;-2.49560;,
 -1.13120;-0.57010;-2.48490;,
 -1.71430;-1.21910;-1.86050;,
 -1.41450;-1.33540;-1.41770;,
 -1.79590;-1.41830;-0.78570;,
 -1.62090;-1.39650;-0.74500;,
 -1.62090;-1.39650;-0.74500;,
 -1.41450;-1.33540;-1.41770;,
 -1.39590;-1.33220;-1.39760;,
 0.84940;1.60910;0.66330;,
 1.07000;0.91660;0.71500;,
 1.65200;0.80780;-0.73560;,
 1.36130;1.52030;-0.74030;,
 1.18600;0.09610;0.83540;,
 1.78810;0.10370;-0.73460;,
 1.65200;0.80780;-0.73560;,
 1.07000;0.91660;0.71500;,
 -1.69860;1.46190;1.63300;,
 -1.69730;0.74390;1.56280;,
 -1.03830;0.99550;1.81910;,
 -0.92040;1.51260;1.63020;,
 1.09020;-0.49590;0.79950;,
 -1.64800;-0.46440;1.43480;,
 -1.91300;-0.42870;1.50760;,
 -1.91300;-0.96780;1.20570;,
 -1.69080;-1.00940;1.24560;,
 0.12820;1.05020;1.54410;,
 -0.04800;1.60210;1.42860;,
 0.41570;-0.31560;1.43700;,
 0.26850;-0.82410;1.34530;,
 -1.10030;-0.41310;1.71050;,
 -1.05570;-0.96280;1.44770;,
 0.14230;-1.34670;1.14920;,
 -1.01140;0.35960;1.90120;,
 -1.53860;-1.36510;0.05520;,
 -1.91300;-1.25020;0.39360;,
 -1.91300;-1.41220;-0.84680;,
 0.30380;0.45620;1.58520;,
 -1.10030;-0.41310;1.71050;,
 -1.01140;0.35960;1.90120;,
 -1.65210;0.13880;1.55420;,
 -1.91300;-0.04390;1.57520;,
 0.12820;1.05020;1.54410;,
 1.40590;0.73900;-1.45720;,
 1.19350;1.40480;-1.51830;,
 -0.90550;1.16600;-2.82740;,
 -0.95350;0.17050;-2.71770;,
 -1.91300;0.02800;-2.77690;,
 -1.91300;1.17770;-2.86080;,
 -0.01340;1.28820;-2.56070;,
 0.02370;0.37650;-2.51710;,
 0.64710;1.36160;-2.08850;,
 0.77820;0.59800;-2.05850;,
 1.47820;0.18200;-1.44590;,
 0.84780;-0.01180;-2.03670;,
 0.77820;0.59800;-2.05850;,
 1.40590;0.73900;-1.45720;,
 -0.88530;1.24000;-2.76910;,
 -1.91300;1.24510;-2.80960;,
 -0.07190;1.35380;-2.50490;,
 0.57120;1.41530;-2.05210;,
 -1.91300;1.54260;1.49220;,
 -1.91300;1.47190;1.57580;,
 -1.60150;1.53010;1.52320;,
 -0.87300;1.56480;1.55920;,
 -0.05460;1.66500;1.39680;,
 0.77750;1.68120;0.67590;,
 1.14850;1.49580;-1.47980;,
 1.27480;1.56470;-0.72700;,
 -0.96240;-1.11700;-1.80500;,
 -1.38230;-1.32990;-1.38300;,
 -0.97670;-1.11970;-1.82850;,
 -1.58550;-1.38660;-0.72790;,
 -1.60050;-1.39080;-0.73510;,
 0.03980;-0.81010;-2.19830;,
 0.02930;-0.82960;-2.17230;,
 -0.99630;-1.12330;-1.86070;,
 0.02160;-0.84380;-2.15320;,
 -1.48430;-1.39570;0.01420;,
 -1.50720;-1.38280;0.03150;,
 -1.53860;-1.36510;0.05520;,
 0.79500;-0.66910;-2.01600;,
 0.77090;-0.69210;-1.95960;,
 0.75330;-0.70890;-1.91840;,
 -1.05040;-1.56300;0.78190;,
 -1.06270;-1.55250;0.82310;,
 -1.07960;-1.53820;0.87930;,
 1.39580;-0.60800;-1.44240;,
 1.38040;-0.64320;-1.41550;,
 1.36920;-0.66900;-1.39580;,
 0.10590;-1.39510;1.06990;,
 0.11820;-1.38740;1.09860;,
 0.13500;-1.37680;1.13790;,
 1.75910;-0.67020;-0.63540;,
 1.73500;-0.70070;-0.62920;,
 1.71880;-0.75050;-0.62450;,
 1.14090;-1.12990;0.62340;,
 1.15930;-1.10950;0.62790;,
 1.18430;-1.08150;0.63400;,
 -1.34160;-1.29710;-1.37350;,
 -0.93010;-1.08850;-1.78710;,
 -1.54080;-1.35270;-0.73160;,
 0.03420;-0.82080;-2.12840;,
 -1.44150;-1.36160;-0.00430;,
 0.75130;-0.68850;-1.89830;,
 -1.01630;-1.52550;0.74810;,
 1.35490;-0.64950;-1.38610;,
 0.11690;-1.36100;1.03030;,
 1.69750;-0.72930;-0.63020;,
 1.13120;-1.10120;0.59270;,
 -1.00370;-1.09310;-1.89480;,
 0.03980;-0.78230;-2.20680;,
 0.79790;-0.63320;-2.01710;,
 0.04000;-0.30100;-2.35390;,
 1.40030;-0.56490;-1.44260;,
 1.76070;-0.62800;-0.64080;,
 1.17920;-1.04960;0.64300;,
 -1.07830;-1.50680;0.91040;,
 -1.69080;-1.00940;1.24560;,
 0.02370;0.37650;-2.51710;,
 -1.91300;0.46980;1.61540;,
 1.13110;-2.16890;-1.48170;,
 0.69480;-0.58180;-1.91980;,
 1.33180;-0.57580;-1.43000;,
 1.69330;-0.62540;-0.60600;,
 -0.92140;-2.20560;-1.49210;,
 -1.02310;-1.14830;-1.80770;,
 -0.08050;-0.67820;-2.16520;,
 0.07530;-2.21770;-1.89090;,
 1.44540;-3.89330;-0.38680;,
 1.43380;-4.01880;-0.37900;,
 1.06080;-4.02390;-1.20650;,
 1.06530;-3.90000;-1.22590;,
 0.04470;-4.06350;-1.57880;,
 0.04480;-3.94480;-1.60320;,
 -0.83680;-4.04590;-1.22040;,
 -0.84220;-3.92120;-1.23960;,
 -1.26600;-3.93140;-0.45180;,
 -1.24990;-4.05570;-0.43670;,
 1.62850;-2.14690;-0.58310;,
 1.24660;-2.27640;0.46440;,
 1.08350;-3.25740;0.43430;,
 1.48070;-3.30080;-0.47030;,
 1.02580;-3.88650;0.41500;,
 1.02890;-4.01350;0.42400;,
 1.09230;-3.29150;-1.31400;,
 1.13110;-2.16890;-1.48170;,
 0.10730;-2.36060;0.96490;,
 0.10270;-3.26750;0.88420;,
 0.08520;-3.91630;0.83210;,
 0.04440;-3.29050;-1.69280;,
 0.07530;-2.21770;-1.89090;,
 -0.96020;-2.27900;0.52270;,
 -0.84390;-3.29530;0.39790;,
 -0.83720;-3.91210;0.41460;,
 -0.85160;-3.29760;-1.31290;,
 -0.92140;-2.20560;-1.49210;,
 -1.45320;-2.20980;-0.59670;,
 -1.32300;-3.30150;-0.50100;,
 -0.83450;-4.03880;0.42450;,
 0.08140;-4.03330;0.83960;,
 1.25880;-1.45100;0.55120;,
 1.24660;-2.27640;0.46440;,
 1.62850;-2.14690;-0.58310;,
 1.17500;-1.05650;0.58640;,
 0.09180;-1.34520;1.08740;,
 0.08870;-1.80030;0.97660;,
 0.10730;-2.36060;0.96490;,
 -1.06840;-1.54740;0.77300;,
 -0.96020;-2.27900;0.52270;,
 -1.51460;-1.29650;-0.01860;,
 -1.45320;-2.20980;-0.59670;,
 -1.60520;-1.35860;-0.71660;,
 -1.40060;-1.31370;-1.40030;,
 -0.80700;-4.74120;-1.11330;,
 0.04450;-4.72630;-1.44250;,
 0.06690;-5.74260;-1.23110;,
 -0.75180;-5.75060;-0.89920;,
 -1.07180;-5.76420;-0.16460;,
 -1.15970;-4.74910;-0.35250;,
 1.03550;-4.71530;-1.09820;,
 0.97310;-5.75800;-0.89390;,
 -0.79820;-5.83700;0.62750;,
 -0.81980;-4.74610;0.47940;,
 1.36950;-4.71890;-0.33530;,
 1.27360;-5.74630;-0.16720;,
 0.06870;-5.85480;1.06330;,
 0.05970;-4.68610;0.88130;,
 1.04610;-4.72210;0.47390;,
 0.96180;-5.81890;0.64050;,
 1.09850;-6.72640;0.85560;,
 1.46070;-6.70190;-0.11530;,
 1.09330;-6.72120;-0.96940;,
 0.11000;-6.74510;1.33210;,
 0.08620;-6.71060;-1.35550;,
 -0.94600;-6.72950;0.80300;,
 -0.85860;-6.72110;-1.00960;,
 -1.26730;-6.68150;-0.13990;,
 0.87230;-7.04400;0.84780;,
 1.18660;-7.36090;1.02590;,
 1.58140;-7.40060;-0.06840;,
 1.15250;-7.07220;-0.04640;,
 1.16070;-7.42790;-1.01030;,
 0.85390;-7.09160;-0.81610;,
 0.14610;-7.04050;1.25890;,
 0.16360;-7.35590;1.52900;,
 0.11360;-7.42450;-1.42490;,
 0.11060;-7.08920;-1.15480;,
 -0.70950;-7.03240;0.76700;,
 -1.04150;-7.34450;0.92700;,
 -0.90910;-7.43720;-1.09180;,
 -0.61550;-7.09820;-0.88270;,
 -1.13360;-6.99170;-0.11720;,
 -1.39540;-7.33270;-0.12590;,
 -1.20900;-3.95300;-0.43460;,
 -0.78020;-3.84110;-1.16860;,
 0.04760;-3.85770;-1.50510;,
 1.00180;-3.82050;-1.15550;,
 1.35210;-3.81570;-0.37840;,
 0.97180;-3.81070;0.37560;,
 0.08200;-3.82930;0.76600;,
 -0.77810;-3.83450;0.37610;,
 -0.94580;-6.86790;-0.08180;,
 -0.61400;-6.92890;-0.75330;,
 0.10210;-6.92030;-0.99460;,
 0.84380;-6.92430;-0.70370;,
 1.13380;-6.90640;-0.04760;,
 0.85790;-6.89160;0.71010;,
 0.13240;-6.89300;1.06490;,
 -0.69930;-6.88400;0.64910;,
 -1.07890;-3.59360;-0.42800;,
 -0.69370;-3.49310;-1.08740;,
 0.05000;-3.50800;-1.38980;,
 0.90730;-3.47460;-1.07570;,
 1.22200;-3.47030;-0.37750;,
 0.88040;-3.46580;0.29990;,
 0.08090;-3.48250;0.65060;,
 -0.69180;-3.48710;0.30030;,
 0.07070;-2.68030;-0.41050;,
 0.10510;-2.67900;-0.39790;,
 0.04080;-2.67970;-0.39840;,
 0.02540;-2.68380;-0.37190;,
 0.04090;-2.67950;-0.34270;,
 0.07190;-2.67930;-0.32860;,
 0.10400;-2.67860;-0.34270;,
 0.11770;-2.67880;-0.36990;,
 -1.03420;0.89850;1.83160;,
 -1.66180;0.26920;1.55610;,
 -1.91300;0.06190;1.58350;,
 -1.11330;-0.56600;-2.48290;,
 -0.01100;0.36920;-2.52420;,
 -1.11330;-0.56600;-2.48290;,
 -0.01100;0.36920;-2.52420;,
 -1.41390;-1.33510;-1.41830;,
 -1.13760;-0.57720;-2.47810;,
 -1.13120;-0.57010;-2.48490;,
 -1.41390;-1.33510;-1.41830;,
 -1.13760;-0.57720;-2.47810;,
 -0.16930;1.65100;1.41960;,
 -0.19360;1.58720;1.46220;,
 -1.41400;-1.33510;-1.41830;,
 -1.41400;-1.33530;-1.41720;,
 -0.62120;-0.45290;-2.42790;,
 -1.06940;-0.82350;-2.19900;,
 -1.68980;-0.99690;1.24990;,
 -1.09920;-0.42660;1.70410;,
 -1.68980;-0.99690;1.24990;,
 -1.09920;-0.42660;1.70410;;
 
 330;
 4;0,1,2,3;,
 3;3,4,5;,
 3;5,4,6;,
 3;7,8,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 3;15,14,22;,
 4;23,24,25,26;,
 4;20,27,28,21;,
 4;11,10,28,27;,
 4;14,29,30,22;,
 4;30,31,32,33;,
 4;31,30,29,34;,
 4;6,35,36,5;,
 3;36,37,5;,
 3;29,38,34;,
 4;23,39,40,41;,
 4;24,23,41,42;,
 4;14,17,43,38;,
 4;13,12,44,45;,
 4;46,47,48,49;,
 4;2,1,48,47;,
 4;50,51,47,46;,
 4;52,53,51,50;,
 4;45,44,53,52;,
 4;54,55,56,57;,
 4;57,16,15,54;,
 4;58,46,49,59;,
 4;60,50,46,58;,
 4;61,52,50,60;,
 4;62,63,18,64;,
 4;64,18,21,65;,
 4;66,28,10,67;,
 4;68,45,52,61;,
 4;69,13,45,68;,
 4;67,10,13,69;,
 4;70,71,9,72;,
 4;73,74,9,71;,
 3;9,74,7;,
 4;75,76,72,77;,
 4;78,70,72,76;,
 4;79,80,74,73;,
 4;81,7,74,80;,
 4;82,83,76,75;,
 4;84,78,76,83;,
 4;85,86,80,79;,
 4;87,81,80,86;,
 4;88,89,83,82;,
 4;90,84,83,89;,
 4;91,92,86,85;,
 4;93,87,86,92;,
 4;94,95,89,88;,
 4;96,90,89,95;,
 4;97,98,92,91;,
 4;99,93,92,98;,
 4;99,98,95,94;,
 4;97,96,95,98;,
 4;100,71,70,101;,
 4;102,73,71,100;,
 4;101,70,78,103;,
 4;104,79,73,102;,
 4;103,78,84,105;,
 4;106,85,79,104;,
 4;105,84,90,107;,
 4;108,91,85,106;,
 4;107,90,96,109;,
 4;110,97,91,108;,
 4;109,96,97,110;,
 4;75,77,111,112;,
 4;55,113,112,114;,
 4;82,75,112,113;,
 4;54,115,113,55;,
 4;88,82,113,115;,
 4;15,116,115,54;,
 4;94,88,115,116;,
 4;22,117,116,15;,
 4;99,94,116,117;,
 4;30,33,117,22;,
 4;93,99,117,33;,
 4;118,33,32,119;,
 4;87,93,33,118;,
 4;118,119,81,87;,
 4;25,36,35,26;,
 4;55,114,120,56;,
 4;63,121,19,18;,
 4;3,5,37,0;,
 3;29,14,38;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,133,132;,
 4;136,137,135,134;,
 4;138,137,136,139;,
 4;140,141,142,143;,
 4;142,144,130,143;,
 4;144,145,131,130;,
 4;130,133,146,143;,
 4;146,147,140,143;,
 4;141,148,149,142;,
 4;149,150,144,142;,
 4;133,135,151,146;,
 4;151,152,147,146;,
 4;148,153,154,149;,
 4;154,155,150,149;,
 4;135,137,156,151;,
 4;156,157,152,151;,
 4;153,158,159,154;,
 4;159,138,155,154;,
 4;137,138,159,156;,
 4;159,158,157,156;,
 4;139,160,155,138;,
 4;150,161,145,144;,
 4;155,160,161,150;,
 4;162,163,164,125;,
 3;162,125,165;,
 4;165,166,167,162;,
 4;167,168,163,162;,
 4;169,170,168,167;,
 3;166,169,167;,
 4;129,128,123,122;,
 4;171,172,170,169;,
 3;172,171,173;,
 4;174,126,172,173;,
 3;126,174,127;,
 3;164,122,125;,
 4;175,176,177,178;,
 4;179,180,175,178;,
 4;176,181,182,177;,
 4;183,184,180,179;,
 4;181,185,186,182;,
 4;187,188,184,183;,
 4;185,189,190,186;,
 4;190,189,188,187;,
 4;186,190,191,192;,
 4;193,182,186,192;,
 4;190,187,194,191;,
 4;195,177,182,193;,
 4;187,183,196,194;,
 4;197,178,177,195;,
 4;183,179,198,196;,
 4;198,179,178,197;,
 4;199,200,201,202;,
 4;202,201,203,204;,
 4;205,206,200,199;,
 4;204,203,207,208;,
 4;209,210,206,205;,
 4;208,207,211,212;,
 4;213,214,210,209;,
 4;212,211,214,213;,
 4;215,136,175,180;,
 4;175,136,134,176;,
 4;176,134,132,181;,
 4;131,185,181,132;,
 4;145,189,185,131;,
 4;161,188,189,145;,
 4;160,184,188,161;,
 4;180,184,160,215;,
 3;215,216,136;,
 4;136,216,217,134;,
 4;134,217,218,132;,
 4;132,218,219,131;,
 4;131,219,220,145;,
 4;145,220,221,161;,
 4;161,221,222,160;,
 3;160,222,215;,
 4;213,223,224,212;,
 4;212,224,225,208;,
 4;208,225,226,204;,
 4;204,226,227,202;,
 4;228,199,202,227;,
 4;229,205,199,228;,
 4;230,209,205,229;,
 4;223,213,209,230;,
 4;223,198,197,224;,
 4;224,197,195,225;,
 4;225,195,193,226;,
 4;226,193,192,227;,
 4;191,228,227,192;,
 4;194,229,228,191;,
 4;196,230,229,194;,
 4;198,223,230,196;,
 4;215,231,232,216;,
 4;216,232,233,217;,
 4;217,233,234,218;,
 4;218,234,235,219;,
 4;219,235,236,220;,
 4;220,236,237,221;,
 4;221,237,238,222;,
 4;222,238,231,215;,
 4;233,239,240,234;,
 4;232,241,239,233;,
 4;231,242,241,232;,
 4;238,243,242,231;,
 4;237,244,243,238;,
 4;236,245,244,237;,
 4;235,246,245,236;,
 4;234,240,246,235;,
 3;43,34,38;,
 3;27,20,40;,
 4;247,248,41,40;,
 4;247,20,19,248;,
 4;248,249,42,41;,
 4;248,19,121,249;,
 4;250,251,120,114;,
 4;252,2,47,253;,
 4;254,255,256,111;,
 4;257,4,3,258;,
 4;259,260,28,66;,
 4;259,65,21,260;,
 3;261,262,8;,
 4;261,72,9,262;,
 3;261,77,72;,
 3;254,261,8;,
 4;254,111,77,261;,
 3;263,264,256;,
 4;263,112,111,264;,
 3;263,114,112;,
 4;265,266,39,23;,
 4;267,119,32,268;,
 4;3,2,1,0;,
 3;5,4,3;,
 3;6,4,5;,
 3;9,8,7;,
 4;13,12,11,10;,
 4;17,16,15,14;,
 4;21,20,19,18;,
 3;22,14,15;,
 4;26,25,24,23;,
 4;21,28,27,20;,
 4;27,28,10,11;,
 4;22,30,29,14;,
 4;33,32,31,30;,
 4;34,29,30,31;,
 4;5,36,35,6;,
 3;5,37,36;,
 3;34,38,29;,
 4;41,40,39,23;,
 4;42,41,23,24;,
 4;38,43,17,14;,
 4;45,44,12,13;,
 4;49,48,47,46;,
 4;47,48,1,2;,
 4;46,47,51,50;,
 4;50,51,53,52;,
 4;52,53,44,45;,
 4;57,56,55,54;,
 4;54,15,16,57;,
 4;59,49,46,58;,
 4;58,46,50,60;,
 4;60,50,52,61;,
 4;64,18,63,62;,
 4;65,21,18,64;,
 4;67,10,28,66;,
 4;61,52,45,68;,
 4;68,45,13,69;,
 4;69,13,10,67;,
 4;72,9,71,70;,
 4;71,9,74,73;,
 3;7,74,9;,
 4;77,72,76,75;,
 4;76,72,70,78;,
 4;73,74,80,79;,
 4;80,74,7,81;,
 4;75,76,83,82;,
 4;83,76,78,84;,
 4;79,80,86,85;,
 4;86,80,81,87;,
 4;82,83,89,88;,
 4;89,83,84,90;,
 4;85,86,92,91;,
 4;92,86,87,93;,
 4;88,89,95,94;,
 4;95,89,90,96;,
 4;91,92,98,97;,
 4;98,92,93,99;,
 4;94,95,98,99;,
 4;98,95,96,97;,
 4;101,70,71,100;,
 4;100,71,73,102;,
 4;103,78,70,101;,
 4;102,73,79,104;,
 4;105,84,78,103;,
 4;104,79,85,106;,
 4;107,90,84,105;,
 4;106,85,91,108;,
 4;109,96,90,107;,
 4;108,91,97,110;,
 4;110,97,96,109;,
 4;112,111,77,75;,
 4;114,112,113,55;,
 4;113,112,75,82;,
 4;55,113,115,54;,
 4;115,113,82,88;,
 4;54,115,116,15;,
 4;116,115,88,94;,
 4;15,116,117,22;,
 4;117,116,94,99;,
 4;22,117,33,30;,
 4;33,117,99,93;,
 4;119,32,33,118;,
 4;118,33,93,87;,
 4;87,81,119,118;,
 4;26,35,36,25;,
 4;56,120,114,55;,
 4;18,19,121,63;,
 4;0,37,5,3;,
 3;38,14,29;,
 3;38,34,43;,
 3;40,20,27;,
 4;40,41,248,247;,
 4;248,19,20,247;,
 4;41,42,249,248;,
 4;249,121,19,248;,
 4;114,120,251,250;,
 4;253,47,2,252;,
 4;111,256,255,254;,
 4;258,3,4,257;,
 4;66,28,260,259;,
 4;260,21,65,259;,
 3;8,262,261;,
 4;262,9,72,261;,
 3;72,77,261;,
 3;8,261,254;,
 4;261,77,111,254;,
 3;256,264,263;,
 4;264,111,112,263;,
 3;112,114,263;,
 4;23,39,266,265;,
 4;268,32,119,267;;
 
 MeshMaterialList {
  3;
  330;
  2,
  2,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  2,
  2,
  1,
  1,
  1,
  2,
  2,
  1,
  2,
  2,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  2,
  2,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  1,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  2,
  2,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  2,
  2,
  1,
  1,
  1,
  2,
  2,
  1,
  2,
  2,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  1,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "chara.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "chara.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "chara.png";
   }
  }
 }
 MeshTextureCoords {
  269;
  0.860075;0.664835;,
  0.860075;0.653602;,
  0.879620;0.648903;,
  0.865043;0.665128;,
  0.872537;0.668035;,
  0.863003;0.670107;,
  0.867378;0.669563;,
  0.162552;0.163713;,
  0.167712;0.162185;,
  0.168177;0.162105;,
  0.929135;0.594423;,
  0.934650;0.611735;,
  0.949200;0.614455;,
  0.941932;0.596642;,
  0.232725;0.126397;,
  0.247777;0.126208;,
  0.244375;0.108605;,
  0.229825;0.105885;,
  0.865435;0.598103;,
  0.865468;0.616053;,
  0.881943;0.609762;,
  0.884890;0.596835;,
  0.230330;0.141198;,
  0.866700;0.646260;,
  0.860075;0.645368;,
  0.860075;0.658845;,
  0.865630;0.659885;,
  0.911105;0.608395;,
  0.906700;0.594598;,
  0.213467;0.136690;,
  0.209787;0.149402;,
  0.175567;0.139127;,
  0.176683;0.152870;,
  0.206632;0.162468;,
  0.177790;0.119810;,
  0.869435;0.668778;,
  0.860075;0.665905;,
  0.860075;0.669955;,
  0.210670;0.117395;,
  0.880392;0.644978;,
  0.882615;0.625660;,
  0.866598;0.631180;,
  0.860075;0.635747;,
  0.206280;0.102545;,
  0.943048;0.616175;,
  0.937737;0.599530;,
  0.885262;0.605500;,
  0.884063;0.630387;,
  0.860075;0.633950;,
  0.860075;0.605208;,
  0.907565;0.602445;,
  0.908493;0.625238;,
  0.924078;0.600610;,
  0.927355;0.619700;,
  0.240030;0.124250;,
  0.224270;0.129095;,
  0.222530;0.113850;,
  0.238222;0.110325;,
  0.885768;0.603650;,
  0.860075;0.603523;,
  0.906103;0.600805;,
  0.922180;0.599267;,
  0.860075;0.596085;,
  0.860075;0.597853;,
  0.867862;0.596398;,
  0.886075;0.595530;,
  0.906535;0.593025;,
  0.927338;0.592620;,
  0.936612;0.597255;,
  0.939770;0.595533;,
  0.179015;0.156725;,
  0.168518;0.162048;,
  0.178658;0.156792;,
  0.163437;0.163465;,
  0.163062;0.163570;,
  0.204070;0.149053;,
  0.203808;0.149540;,
  0.178167;0.156882;,
  0.203615;0.149895;,
  0.165967;0.163693;,
  0.165395;0.163370;,
  0.164610;0.162928;,
  0.222950;0.145528;,
  0.222347;0.146103;,
  0.221907;0.146522;,
  0.176815;0.167875;,
  0.176508;0.167612;,
  0.176085;0.167255;,
  0.237970;0.144000;,
  0.237585;0.144880;,
  0.237305;0.145525;,
  0.205722;0.163678;,
  0.206030;0.163485;,
  0.206450;0.163220;,
  0.247052;0.145555;,
  0.246450;0.146318;,
  0.246045;0.147563;,
  0.231597;0.157048;,
  0.232057;0.156538;,
  0.232682;0.155838;,
  0.169535;0.161227;,
  0.179823;0.156013;,
  0.164555;0.162618;,
  0.203930;0.149320;,
  0.167037;0.162840;,
  0.221857;0.146013;,
  0.177667;0.166938;,
  0.236948;0.145038;,
  0.205997;0.162825;,
  0.245512;0.147032;,
  0.231355;0.156330;,
  0.177982;0.156128;,
  0.204070;0.148358;,
  0.223022;0.144630;,
  0.204075;0.136325;,
  0.238082;0.142922;,
  0.247092;0.144500;,
  0.232555;0.155040;,
  0.176117;0.166470;,
  0.160805;0.154035;,
  0.203667;0.119388;,
  0.860075;0.622905;,
  0.231353;0.183022;,
  0.220445;0.143345;,
  0.236370;0.143195;,
  0.245407;0.144435;,
  0.180040;0.183940;,
  0.177497;0.157508;,
  0.201063;0.145755;,
  0.204957;0.184243;,
  0.810935;0.656958;,
  0.810645;0.660095;,
  0.801320;0.660223;,
  0.801432;0.657125;,
  0.775918;0.661213;,
  0.775920;0.658245;,
  0.753880;0.660773;,
  0.753745;0.657655;,
  0.743150;0.657910;,
  0.743553;0.661017;,
  0.815513;0.613298;,
  0.805965;0.616535;,
  0.801888;0.641060;,
  0.811818;0.642145;,
  0.800445;0.656788;,
  0.800523;0.659963;,
  0.802108;0.641913;,
  0.803078;0.613847;,
  0.777483;0.618640;,
  0.777367;0.641312;,
  0.776930;0.657533;,
  0.775910;0.641887;,
  0.776682;0.615067;,
  0.750795;0.616600;,
  0.753703;0.642007;,
  0.753870;0.657427;,
  0.753510;0.642065;,
  0.751765;0.614765;,
  0.738470;0.614870;,
  0.741725;0.642163;,
  0.753937;0.660595;,
  0.776835;0.660457;,
  0.234545;0.165075;,
  0.234240;0.185710;,
  0.243787;0.182472;,
  0.232450;0.155212;,
  0.205370;0.162430;,
  0.205292;0.173808;,
  0.205757;0.187815;,
  0.176365;0.167485;,
  0.179070;0.185775;,
  0.165210;0.161213;,
  0.166745;0.184045;,
  0.162945;0.162765;,
  0.168060;0.161642;,
  0.754625;0.678155;,
  0.775913;0.677782;,
  0.776473;0.703190;,
  0.756005;0.703390;,
  0.748005;0.703730;,
  0.745808;0.678352;,
  0.800687;0.677508;,
  0.799127;0.703575;,
  0.754845;0.705550;,
  0.754305;0.678277;,
  0.809038;0.677598;,
  0.806640;0.703282;,
  0.776518;0.705995;,
  0.776293;0.676777;,
  0.800952;0.677678;,
  0.798845;0.705097;,
  0.802263;0.727785;,
  0.811318;0.727172;,
  0.802132;0.727655;,
  0.777550;0.728253;,
  0.776955;0.727390;,
  0.751150;0.727862;,
  0.753335;0.727652;,
  0.743118;0.726663;,
  0.796607;0.735725;,
  0.804465;0.743648;,
  0.814335;0.744640;,
  0.803612;0.736430;,
  0.803818;0.745322;,
  0.796147;0.736915;,
  0.778453;0.735637;,
  0.778890;0.743523;,
  0.777640;0.745237;,
  0.777565;0.736855;,
  0.757062;0.735435;,
  0.748762;0.743237;,
  0.752073;0.745555;,
  0.759413;0.737080;,
  0.746460;0.734417;,
  0.739915;0.742943;,
  0.744575;0.658450;,
  0.755295;0.655653;,
  0.775990;0.656067;,
  0.799845;0.655137;,
  0.808603;0.655017;,
  0.799095;0.654893;,
  0.776850;0.655357;,
  0.755347;0.655488;,
  0.751155;0.731323;,
  0.759450;0.732848;,
  0.777353;0.732633;,
  0.795895;0.732733;,
  0.803145;0.732285;,
  0.796247;0.731915;,
  0.778110;0.731950;,
  0.757318;0.731725;,
  0.747828;0.649465;,
  0.757457;0.646953;,
  0.776050;0.647325;,
  0.797482;0.646490;,
  0.805350;0.646383;,
  0.796810;0.646270;,
  0.776823;0.646688;,
  0.757505;0.646802;,
  0.776567;0.626633;,
  0.777427;0.626600;,
  0.775820;0.626617;,
  0.775435;0.626720;,
  0.775823;0.626612;,
  0.776597;0.626608;,
  0.777400;0.626590;,
  0.777743;0.626595;,
  0.882045;0.612188;,
  0.866355;0.627920;,
  0.860075;0.633103;,
  0.175242;0.142950;,
  0.202800;0.119570;,
  0.880067;0.648800;,
  0.907625;0.625420;,
  0.167728;0.162178;,
  0.174635;0.143230;,
  0.174795;0.143053;,
  0.872553;0.668028;,
  0.879460;0.649080;,
  0.903668;0.593375;,
  0.903060;0.594970;,
  0.167725;0.162178;,
  0.167725;0.162183;,
  0.187545;0.140123;,
  0.176340;0.149388;,
  0.865655;0.659572;,
  0.880420;0.645315;,
  0.160830;0.153722;,
  0.175595;0.139465;;
 }
}
