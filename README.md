# Skilgreining
Í dæminu Alpine Valley frá BOI 2019 (Baltic Olympiad in Informatics) er okkur gefið að við höfum **_N_** bæji með **_N-1_** vegi á milli sýn, allir mismunandi að lengd. Okkur er líka gefið að þú getur komist frá hverjum bæ í alla hina.

Í dæminu Alpine Valley frá BOI 2019 (Baltic Olympiad in Informatics) er okkur gefið tré með **_N_** nóðum með sérstaka útgangs eða exit nóðu **_E_**. Einnig eru **_S_** sérstakar nóður sem hafa búðir.
Við þurfum að geta svarað **_Q_** fyrispurnum af þessu formi: Ef við myndum tímabundið eiða legg **_I_**.
* Er hægt að komast að nóðu **_E_** frá nóðu **_R_** (án þess að nota legg **_I_**)?
* Ef ekki er hægt að komast í búð frá **_R_** (án þess að nota legg **_I_**)?
* Ef svo hver er styðsta búðin frá **_R_** (án þess að nota legg **_I_**)?

Þar sem að 1 ≤ **_S_** ≤ **_N_** ≤ 10<sup>5</sup>, 1 ≤ **_Q_** ≤ 10<sup>5</sup> og við gefum forritinu 3 sekúndur í keyrslu.

## Lausn á minna dæmi
Ef við hugsum okkur að 1 ≤ **_N_**, **_Q_** ≤ 10<sup>4</sup> þá er þetta ekkert rosalega erfitt dæmi. Eina sem við þurfum að gera er BFS (Breadth First Search) yfir tréið frá **_R_** án þess að nota legg **_I_**.
![bfs](https://piskel-imgstore-b.appspot.com/img/25ca7947-7568-11e9-9c69-014fc5b19ac6.gif)

Meðan við göngum í gegnum tréð skulum við alltaf geyma stiðstu vegalengd í búð sem við höfum heimsótt (byrjar sem ∞) og ef við hittum á útgangs nóðuna hættum við að ganga.
Þetta gefur okkur tímaflækjuna O(**_NQ_**). Það þýðir að í versta falli höfum við O(10<sup>8</sup>) fyrir minna dæmið en O(10<sup>10</sup>) fyrir hið stærra. Það er of mikið.

## Lausnin
Ef við viljum betri lausn þarf að hugsa um tréð sem rótað tré (rooted tree) með **_E_** sem rótina. Ástæðan fyrir því er að ef við eiðum legg **_I_** og segjum að nóða **_u_** sé lægri nóða leggsins (nóðan sem er lengra frá **_E_**), þá vitum við að ef **_R_** er í hluttré **_u_** þá er ekki hægt að komast frá **_R_** til **_E_**.

Nú er spurningin hvernig við athugum hvort **_R_** sé í hluttré **_u_**. Heppilega er það frekar létt að athuga. Við gerum DFS (Depth First Search) yfir tréð í byrjun og geymum hvenær við göngum í og úr nóðu. Við vitum þá að **_R_** sé í hluttré **_u_** ef <b><i>enter<sub>u</sub> ≤ enter<sub>R</sub> ≤ exit<sub>u</sub></i></b> sé satt.

![dfs](https://piskel-imgstore-b.appspot.com/img/a51438fa-7579-11e9-828e-014fc5b19ac6.gif)
