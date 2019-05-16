# Skilgreining

Í dæminu [Alpine Valley](http://boi2019.eio.ee/wp-content/uploads/2019/04/valley.en_.pdf) frá [BOI 2019](http://boi2019.eio.ee/) (Baltic Olympiad in Informatics) er okkur gefið tré með **_N_** nóðum með sérstaka útgangs eða exit nóðu **_E_**. Einnig eru **_S_** sérstakar nóður sem hafa búðir.
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

Nú er spurningin hvernig við athugum hvort **_R_** sé í hluttré **_u_**. Heppilega er það frekar létt að athuga. Við gerum DFS (Depth First Search) yfir tréð frá **_E_** í byrjun keyrslu og geymum hvenær við göngum í og úr nóðu. Við vitum þá að **_R_** sé í hluttré **_u_** ef <b><i>enter<sub>u</sub> ≤ enter<sub>R</sub> ≤ exit<sub>u</sub></i></b> sé satt.

![dfs](https://piskel-imgstore-b.appspot.com/img/a51438fa-7579-11e9-828e-014fc5b19ac6.gif)

Með þessari DFS yfirferð getum við svarað öllum fyrirspurnum þar sem ekki er hægt að komast frá **_R_** í **_E_** í O(1) tíma með fyrirfram reiknum sem tekur O(**_N_**) tíma.

Nú er síðasti hluti dæmissins, hvar er styðsta búðin. Fyrir það þurfum við að nota aðferð sem kallast tvíundarhopp (binary jumping eða binary lifting). Segjum að <b><i>dist<sub>E</sub></i>[V]</b> sé vegalend einhverrar nóðu **_V_** frá **_E_**. Segjum einnig að **_P_** sé styðsta búðin frá **_R_** sem við viljum finna. Fyrst að þetta er rótað tré þá getum við vitað lengdina á milli **_R_** og **_P_** ef við vitum lca(**_R_**,**_P_**) þar sem lca þýðir fyrsti sameiginlegi forfaðir (lowest common ancestor). Vegalengdin á milli **_R_** og **_P_** er þá <b><i>dist<sub>E</sub>[R] + dist<sub>E</sub>[P] - 2dist<sub>E</sub>[lca(R,P)]</i></b>. Fyrst við vitum bara **_R_** í þessari formúlu þurfum við að finna restina. Ef við segjum að <b><i>mag[U] = dist<sub>E</sub>[P] - 2dist<sub>E</sub>[U]</i></b> þar sem **_P_** sé búðin styðst frá **_U_** í hluttré **_U_** (mag stutt fyrir magnitude). Þá vitum við að ef **_P_** sé styðsta búðin frá **_R_** þá er lengdin á milli **_R_** og **_P_**: <b><i>dist<sub>E</sub>[R] + mag[U]</i></b>.

![jmp](https://puu.sh/Do80N/217d9cbc87.png)

Ef við skoðum tréð hér að ofan þar sem er skorið á legg **_(w,v)_** og spurt um nóðu **_x_**. Hér vitum við að svarið sé <b><i>dist<sub>E</sub>[x] + </i></b>**_min(mag[x], mag[y], mag[z], mag[u], mag[v])_**.

Þessi aðferð hentar líka vel fyrst það er hægt að búa til **_dist_** og **_mag_** í DFS kallinu okkar í byrjun. En þessi aðferð er samt ennþá með tímaflækjuna O(**_N_**). Hér þurfum við að nýta okkur tvíundarhopp.

![Lift](https://piskel-imgstore-b.appspot.com/img/79fcae91-762d-11e9-ad6d-b95f354db464.gif)

Segjum að við myndum hoppa í gegnum tréð í veldum af 2 og byrjum á 0. Þá myndi fyrsta hoppið vera upp um eina nóðu svo tvær og svo fjórar etc. Meðan við erum að hoppa viljum við bæði geyma hvaða nóðu við lendum á og hvert er stiðsta vegalengdin samkvæmt hoppunum. Geymum þessar upplýsingar í tvívíddum listum **_jmpv_** (stutt fyrir jumpVertex) og **_jmpm_** (sutt fyrir jumpMagnitude). Við vitum að **_jmpv[i][0] = foreldri i, jmpm[i][0] = mag[i]_** og **_jmp[i][j] = jmpv[jmpv[i][j-1]][j-1], jmpm[i][j] = min(jmpm[i][j-1],jmpm[jmpv[i][j-1]][j-1])_**. Við vitum að þetta sé satt útaf því að hoppa tvo upp í tréinu er hið sama og að hoppa einu sinni tvisvar.

![lift2](https://piskel-imgstore-b.appspot.com/img/da39c251-7631-11e9-adcb-5777ae719b66.gif)

Eftir að búa til **_jmpv_** og **_jmpm_** (sem að tekur **_N log N_** tíma) getum við fundið minnsta **_mag[U]_** með því að hoppa eins hátt og við getum sem mun aldrei vera meira en **_log N_** hopp.

Þá erum við loks komin með tímaflækjuna O(**_(N + Q) log N_**).
