#!/bin/bash
t=`date +%Y.%h.%d-%H.%d.%S`
(
sleep 2;
echo -e "\r";
sleep 1;
echo -e "read (0-15,0-15) \r";
sleep 5;
echo -e "set voltage limit 1600 \r";
echo -e "\r";
echo -e "write (0-15,0-15) -900\r"; sleep 2;

echo -e "write (0,0) -1432\r"; sleep 2;
echo -e "write (0,1) -1400\r"; sleep 2;
echo -e "write (0,2) -1442\r"; sleep 2;
echo -e "write (0,3) -1499\r"; sleep 2;
echo -e "write (0,4) -1394\r"; sleep 2;
echo -e "write (0,5) -1400\r"; sleep 2;
echo -e "write (0,6) -1381\r"; sleep 2;
echo -e "write (0,9) -1378\r"; sleep 2;
echo -e "write (0,10) -1411\r"; sleep 2;
echo -e "write (0,11) -1378\r"; sleep 2;
echo -e "write (0,12) -1444\r"; sleep 2;
echo -e "write (0,13) -1410\r"; sleep 2;
echo -e "write (0,14) -1451\r"; sleep 2;
echo -e "write (1,0) -1401\r"; sleep 2;
echo -e "write (1,1) -1417\r"; sleep 2;
echo -e "write (1,2) -1366\r"; sleep 2;
echo -e "write (1,3) -1387\r"; sleep 2;
echo -e "write (1,4) -1385\r"; sleep 2;
echo -e "write (1,5) -1439\r"; sleep 2;
echo -e "write (1,6) -1420\r"; sleep 2;
echo -e "write (1,9) -1380\r"; sleep 2;
echo -e "write (1,10) -1400\r"; sleep 2;
echo -e "write (1,11) -1372\r"; sleep 2;
echo -e "write (1,12) -1406\r"; sleep 2;
echo -e "write (1,13) -1400\r"; sleep 2;
echo -e "write (1,14) -1434\r"; sleep 2;
echo -e "write (2,0) -1095\r"; sleep 2;
echo -e "write (2,1) -1381\r"; sleep 2;
echo -e "write (2,2) -1400\r"; sleep 2;
echo -e "write (2,3) -1400\r"; sleep 2;
echo -e "write (2,4) -1410\r"; sleep 2;
echo -e "write (2,5) -1411\r"; sleep 2;
echo -e "write (2,6) -1334\r"; sleep 2;
echo -e "write (2,9) -1399\r"; sleep 2;
echo -e "write (2,10) -1400\r"; sleep 2;
echo -e "write (2,11) -1405\r"; sleep 2;
echo -e "write (2,12) -1347\r"; sleep 2;
echo -e "write (2,13) -1065\r"; sleep 2;
echo -e "write (2,14) -1062\r"; sleep 2;
echo -e "write (3,0) -1361\r"; sleep 2;
echo -e "write (3,1) -1391\r"; sleep 2;
echo -e "write (3,2) -1400\r"; sleep 2;
echo -e "write (3,3) -1394\r"; sleep 2;
echo -e "write (3,4) -1388\r"; sleep 2;
echo -e "write (3,5) -1400\r"; sleep 2;
echo -e "write (3,6) -1400\r"; sleep 2;
echo -e "write (3,9) -1384\r"; sleep 2;
echo -e "write (3,10) -1430\r"; sleep 2;
echo -e "write (3,11) -1330\r"; sleep 2;
echo -e "write (3,12) -1419\r"; sleep 2;
echo -e "write (3,13) -1316\r"; sleep 2;
echo -e "write (3,14) -1343\r"; sleep 2;
echo -e "write (4,0) -1239\r"; sleep 2;
echo -e "write (4,1) -1537\r"; sleep 2;
echo -e "write (4,2) -1373\r"; sleep 2;
echo -e "write (4,3) -1365\r"; sleep 2;
echo -e "write (4,4) -1410\r"; sleep 2;
echo -e "write (4,5) -1400\r"; sleep 2;
echo -e "write (4,6) -1400\r"; sleep 2;
echo -e "write (4,9) -1394\r"; sleep 2;
echo -e "write (4,10) -1514\r"; sleep 2;
echo -e "write (4,11) -1378\r"; sleep 2;
echo -e "write (4,12) -1426\r"; sleep 2;
echo -e "write (4,13) -1400\r"; sleep 2;
echo -e "write (4,14) -1437\r"; sleep 2;
echo -e "write (5,0) -1358\r"; sleep 2;
echo -e "write (5,1) -1336\r"; sleep 2;
echo -e "write (5,2) -1587\r"; sleep 2;
echo -e "write (5,3) -1375\r"; sleep 2;
echo -e "write (5,4) -1183\r"; sleep 2;
echo -e "write (5,5) -1443\r"; sleep 2;
echo -e "write (5,6) -1272\r"; sleep 2;
echo -e "write (5,9) -1382\r"; sleep 2;
echo -e "write (5,10) -1388\r"; sleep 2;
echo -e "write (5,11) -1355\r"; sleep 2;
echo -e "write (5,12) -1400\r"; sleep 2;
echo -e "write (5,13) -1426\r"; sleep 2;
echo -e "write (5,14) -1435\r"; sleep 2;
echo -e "write (6,0) -1303\r"; sleep 2;
echo -e "write (6,1) -1384\r"; sleep 2;
echo -e "write (6,2) -1341\r"; sleep 2;
echo -e "write (6,3) -1375\r"; sleep 2;
echo -e "write (6,4) -1376\r"; sleep 2;
echo -e "write (6,5) -1365\r"; sleep 2;
echo -e "write (6,6) -1366\r"; sleep 2;
echo -e "write (6,9) -1420\r"; sleep 2;
echo -e "write (6,10) -1393\r"; sleep 2;
echo -e "write (6,11) -1400\r"; sleep 2;
echo -e "write (6,12) -1554\r"; sleep 2;
echo -e "write (6,13) -1501\r"; sleep 2;
echo -e "write (6,14) -1297\r"; sleep 2;
echo -e "write (7,0) -1389\r"; sleep 2;
echo -e "write (7,1) -1371\r"; sleep 2;
echo -e "write (7,2) -1379\r"; sleep 2;
echo -e "write (7,3) -1361\r"; sleep 2;
echo -e "write (7,4) -1368\r"; sleep 2;
echo -e "write (7,5) -1375\r"; sleep 2;
echo -e "write (7,6) -1439\r"; sleep 2;
echo -e "write (7,9) -1381\r"; sleep 2;
echo -e "write (7,10) -1415\r"; sleep 2;
echo -e "write (7,11) -1402\r"; sleep 2;
echo -e "write (7,12) -1368\r"; sleep 2;
echo -e "write (7,13) -1395\r"; sleep 2;
echo -e "write (7,14) -1407\r"; sleep 2;
echo -e "write (8,0) -1380\r"; sleep 2;
echo -e "write (8,1) -1368\r"; sleep 2;
echo -e "write (8,2) -1323\r"; sleep 2;
echo -e "write (8,3) -1395\r"; sleep 2;
echo -e "write (8,4) -1404\r"; sleep 2;
echo -e "write (8,5) -1432\r"; sleep 2;
echo -e "write (8,6) -1453\r"; sleep 2;
echo -e "write (8,9) -1385\r"; sleep 2;
echo -e "write (8,10) -1396\r"; sleep 2;
echo -e "write (8,11) -1517\r"; sleep 2;
echo -e "write (8,12) -1389\r"; sleep 2;
echo -e "write (8,13) -1366\r"; sleep 2;
echo -e "write (8,14) -1398\r"; sleep 2;
echo -e "write (9,0) -1381\r"; sleep 2;
echo -e "write (9,1) -1089\r"; sleep 2;
echo -e "write (9,2) -1413\r"; sleep 2;
echo -e "write (9,3) -1409\r"; sleep 2;
echo -e "write (9,4) -1402\r"; sleep 2;
echo -e "write (9,5) -1397\r"; sleep 2;
echo -e "write (9,6) -1376\r"; sleep 2;
echo -e "write (9,9) -1366\r"; sleep 2;
echo -e "write (9,10) -1417\r"; sleep 2;
echo -e "write (9,11) -1446\r"; sleep 2;
echo -e "write (9,12) -1400\r"; sleep 2;
echo -e "write (9,13) -1371\r"; sleep 2;
echo -e "write (9,14) -1422\r"; sleep 2;
echo -e "write (10,0) -1472\r"; sleep 2;
echo -e "write (10,1) -1400\r"; sleep 2;
echo -e "write (10,2) -1355\r"; sleep 2;
echo -e "write (10,3) -1371\r"; sleep 2;
echo -e "write (10,4) -1402\r"; sleep 2;
echo -e "write (10,5) -1374\r"; sleep 2;
echo -e "write (10,6) -1461\r"; sleep 2;
echo -e "write (10,9) -1400\r"; sleep 2;
echo -e "write (10,10) -1376\r"; sleep 2;
echo -e "write (10,11) -1387\r"; sleep 2;
echo -e "write (10,12) -1400\r"; sleep 2;
echo -e "write (10,13) -1391\r"; sleep 2;
echo -e "write (10,14) -1396\r"; sleep 2;
echo -e "write (11,0) -1360\r"; sleep 2;
echo -e "write (11,1) -1371\r"; sleep 2;
echo -e "write (11,2) -1375\r"; sleep 2;
echo -e "write (11,3) -1408\r"; sleep 2;
echo -e "write (11,4) -1412\r"; sleep 2;
echo -e "write (11,5) -1435\r"; sleep 2;
echo -e "write (11,6) -1384\r"; sleep 2;
echo -e "write (11,9) -1516\r"; sleep 2;
echo -e "write (11,10) -1389\r"; sleep 2;
echo -e "write (11,11) -1572\r"; sleep 2;
echo -e "write (11,12) -1370\r"; sleep 2;
echo -e "write (11,13) -1401\r"; sleep 2;
echo -e "write (11,14) -1454\r"; sleep 2;
echo -e "write (12,0) -1408\r"; sleep 2;
echo -e "write (12,1) -1378\r"; sleep 2;
echo -e "write (12,2) -1378\r"; sleep 2;
echo -e "write (12,3) -1558\r"; sleep 2;
echo -e "write (12,4) -1400\r"; sleep 2;
echo -e "write (12,5) -1431\r"; sleep 2;
echo -e "write (12,6) -1394\r"; sleep 2;
echo -e "write (12,9) -1409\r"; sleep 2;
echo -e "write (12,10) -1583\r"; sleep 2;
echo -e "write (12,11) -1444\r"; sleep 2;
echo -e "write (12,12) -1432\r"; sleep 2;
echo -e "write (12,13) -1389\r"; sleep 2;
echo -e "write (12,14) -1434\r"; sleep 2;
echo -e "write (13,0) -1583\r"; sleep 2;
echo -e "write (13,1) -1542\r"; sleep 2;
echo -e "write (13,2) -1427\r"; sleep 2;
echo -e "write (13,3) -1396\r"; sleep 2;
echo -e "write (13,4) -1472\r"; sleep 2;
echo -e "write (13,5) -1356\r"; sleep 2;
echo -e "write (13,6) -1569\r"; sleep 2;
echo -e "write (13,9) -1483\r"; sleep 2;
echo -e "write (13,10) -900\r"; sleep 2;
echo -e "write (13,11) -1435\r"; sleep 2;
echo -e "write (13,12) -1462\r"; sleep 2;
echo -e "write (13,13) -1400\r"; sleep 2;
echo -e "write (13,14) -1411\r"; sleep 2;
echo -e "write (14,0) -1396\r"; sleep 2;
echo -e "write (14,1) -1417\r"; sleep 2;
echo -e "write (14,2) -1492\r"; sleep 2;
echo -e "write (14,3) -1550\r"; sleep 2;
echo -e "write (14,4) -1532\r"; sleep 2;
echo -e "write (14,5) -1477\r"; sleep 2;
echo -e "write (14,6) -1400\r"; sleep 2;
echo -e "write (14,9) -1393\r"; sleep 2;
echo -e "write (14,10) -1374\r"; sleep 2;
echo -e "write (14,11) -1400\r"; sleep 2;
echo -e "write (14,12) -1532\r"; sleep 2;
echo -e "write (14,13) -1400\r"; sleep 2;
echo -e "write (14,14) -1483\r"; sleep 2;
echo -e "write (15,0) -1391\r"; sleep 2;
echo -e "write (15,1) -1337\r"; sleep 2;

sleep 2;
echo -e "read (0-15,0-15)\r";
sleep 10;
echo -e "\r";
echo -e "\r";
echo -e "^]";
sleep 1;
) | telnet fms-serv.trg.bnl.local 7005 > ../hvlog_run11/fms_hv2_7005_$t.tex
echo Set new HV
cat ../hvlog_run11/fms_hv2_7005_$t.tex