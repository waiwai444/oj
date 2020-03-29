#include <stdio.h>
#include <string.h>
#include <map>
#include <string>

const int result_num = 480;
bool valid_result[24];
char result[24][500][28] = {{
	"aaabbebeeaddddgffecccfcgfgg",
	"aaabbfbffaddddfeggcccecgeeg",
	"aaabbfbddaffggfddecccgcegee",
	"aaabbdbedafdgedgeeffcfccggc",
	"aaabbebeeafdgddgdeffcfccggc",
	"aaabbebeeaffgddddeggfgcfccc",
	"aaabbebddaffgeeddeggfgcfccc",
	"aaabbdbgdafdgfdggecffccecee",
	"aaabbebeeadgddgdfecggccfcff",
	"aaabbgbggadeddfdgfceeccecff",
	"aaabbdbfdacdffdgfecccggegee",
	"aaabbdbgdacdgfdggecccffefee",
	"aaabbebeeacfggfddecccgffgdd",
	"aaabbebeeaddfggfceddgffgccc",
	"aaabbebeeafdcfdggecffcgdcgd",
	"aaabbfbddaffcgfddecggcgecee",
	"aaabbgbddagfcggddecffcfecee",
	"aaabbebeeaggdfcdfedgcdgcffc",
	"aaaeggeegaddfbbebgddcfccffc",
	"aaaggfgddaffcgfddecbbcbecee",
	"aaafcdcccagdfgdffeggdbbebee",
	"aaaffefeeacdggdfgecccbbdbgd",
	"aaaggegeeacdfgdffecccbbdbfd",
	"aaafggfddacgffgddecccbbebee",
	"aaaffefeeaddggcfgeddcbbcbgc",
	"aaaggegeeaddfgcffeddcbbcbfc",
	"aaafbbfdbaggffgeddcccecgeed",
	"aaafbbffbadgddgdfecggccecee",
	"aaaebbeebacdfgdeggcccfgdffd",
	"aaaebbeebacdggdeffcccgfdgfd",
	"aaagbbggbacdgddedfccceffeef",
	"aaaebbeebaffgfdecdggdgfdccc",
	"aaaebbeebaggffdecdfgdfgdccc",
	"aaaebbeebaddfgceggddcfgcffc",
	"aaaebbeebaddggceffddcgfcgfc",
	"aaaebbeebaffgfceddggcgfcddc",
	"aaaebbeebaggffceddfgcfgcddc",
	"aaaeffeefabbgfbeddggcgccddc",
	"aaagcdcccaffggdegdbbfebfeed",
	"aaaecdcccaffeedegdbbfgbfggd",
	"aaafcdcccafdffdeggbbdebgeeg",
	"aaagddddcaffggcegcbbfebfeec",
	"aaaeddddcaffeecegcbbfgbfggc",
	"aaaeddeecaffddcegcbbfgbfggc",
	"aaaffefeeaddddcfgebbcgbcggc",
	"aaafggffgaddddcefgbbcebceec",
	"aaagfdggdacdgfdeffcccebbeeb",
	"aaafgdfgdacdffdeggcccebbeeb",
	"aaaeggeegacdfddedgcccfbbffb",
	"aaaeffeedafgcfgeddcggcbbcdb",
	"aaaeggeedafgcfgeddcffcbbcdb",
	"aaafbdbbdafdffdeggcccecgeeg",
	"aaagbdbbdacdggdegfccceffeef",
	"aaaebdbbdacdeedegfcccgffggf",
	"aaaffefeeabdbbdfgecccgcdggd",
	"aaafggffgabdbbdefgcccecdeed",
	"aaagffggfaddgfbebbddcecceec",
	"aaafggfgcaddffgeccddbebbeec",
	"aaageegecaddfecggcddbfbbffc",
	"aaaeggeecaddfgcegcddbfbbffc",
	"aaaggegeeaffdgfdcedfbdbbccc",
	"aaaggegeeaffcgfddecfbcbbcdd",
	"aaaecdcccafdeedeggffdfbgbbg",
	"aaafggffgacdeedefgcccebdbbd",
	"aaaeggeegacdffdefgcccfbdbbd",
	"aaafggffgaddeecefgddcebcbbc",
	"aaaeggeegaddffcefgddcfbcbbc",
	"aaafggffgaeedecdfgdecdbcbbc",
	"aaagbegbbaddfeeggeddcfccffc",
	"aaafbgfbbaddffgeggddcecceec",
	"aaagbdgbbafdffdggecfdccecee",
	"aaafggffgabedbbdfgdeedceccc",
	"aaaggdcgdafdcfdcgebffbbecee",
	"aaadffcccafgdfgdcebggbbedee",
	"aaadggcccafgdfgdcebffbbedee",
	"aaaeggeegaddddfecgbffbbfccc",
	"aaaddeceeaffgddcceggfgbfcbb",
	"aaaddecddaffgeecceggfgbfcbb",
	"aaaffgfggadecddfgdceecbecbb",
	"aaaefdeedagdcfdeffcggcbgcbb",
	"aaaffdfedagdcedfeecggcbgcbb",
	"aaaffgfggaeecedfgdcedcbdcbb",
	"aaaffefeeagdcddfdecggcbgcbb",
	"aaabffbdfaggbfgeddcccecgeed",
	"aaabffbddafgbfgddecggccecee",
	"aaabggbddafgbfgddecffccecee",
	"aaabgebeeaggbgfddecffccfcdd",
	"aaabfebeeagfbffddecggccgcdd",
	"aaabfgbffagebggddfceeccecdd",
	"aaabffbggafebfgddgceeccecdd",
	"aaabfebffagebeeddfcggccgcdd",
	"aaabggbgcaddbfgeccddfeffeec",
	"aaabffbfcaggbgcefcddgeddeec",
	"aaabggbddacgbfgddecccffefee",
	"aaagfbggbaddgfbeffddcecceec",
	"aaafgbfgbaddffbeggddcecceec",
	"aaagdbgdbadfcdbggecffcfecee",
	"aaaeffeecafbgfbeccggbgddddc",
	"aaagffggcafbgfbeccddbeddeec",
	"aaaggegeeafbdgbdcedfbdffccc",
	"aaaeggeegafbddbecgffbfddccc",
	"aaaffefeeagbggbfceddbgddccc",
	"aaaggegeeafbcgbddecfbcffcdd",
	"aaaeggeegacdfbdebgcccfbdffd",
	"aaaeggeegaddfbcebgddcfbcffc",
	"aaaebbeegaddfgbeggddcfccffc",
	"aaagbbggcaddgfbeccddfeffeec",
	"aaaebbeecaggfgbeccddgfddffc",
	"aaafggbbgafdffdebgcccecdeed",
	"aaaggdbbdafdgfdgbecffccecee",
	"aaaggdbbdacdgfdgbecccffefee",
	"aaaedfeefabbgddeffggbgcdccc",
	"aaafggfgcabbffgeccddbeddeec",
	"aaageegecabbfecggcddbfddffc",
	"aaaeggeecabbfgcegcddbfddffc",
	"aaaeggeegabbcffefgcdbcddcfd",
	"aaaeffeefabbcfgeggcdbcddcgd",
	"aaaffefeeabbcdgfdecdbcdgcgg",
	"aaaffefeeacdbbdfgecccgbdggd",
	"aaafggffgacdbbdefgcccebdeed",
	"aaaffefeeaddbbcfgeddcgbcggc",
	"aaafggffgaddbbcefgddcebceec",
	"aaaggfcffagecgfcbbdeeddecdb",
	"aaafbdfbdacdffdgbecccggegee",
	"aaaggegeeacdbgdbfecccffdbfd",
	"aaafggffgacdbedbfgccceedbed",
	"aaafggffgacebeebfgcccddebdd",
	"aaafggffgaeebecbfgdecddcbdc",
	"aaaggegeeaddbgcbfeddcffcbfc",
	"aaafggffgaddbecbfgddceecbec",
	"aaaffgfggadecdbfgbceecdecdb",
	"aaaffgfggaeecebfgbcedcddcdb",
	"aaabbdcccagdbgdecfggdeffeef",
	"aaabbdggdacdbgdegfccceffeef",
	"aaagffggcafegfcbbcdeeddebdc",
	"aaagbdggdacdgbdebfccceffeef",
	"aaaggfgddaffbgfddecccbcebee",
	"aaaeggeegaddbffefgddcbccbfc",
	"aaaeffeefaddbfgeggddcbccbgc",
	"aaaggegeeacfbgfddecccbffbdd",
	"aaaffefeeaddddbfgecccgcbggb",
	"aaafggffgaddddbefgcccecbeeb",
	"aaaggedeeagfcgbddecffcfbcdb",
	"aaaebdeedacdbbdegfcccgffggf",
	"aaafbdffdacdbbdgfecccggegee",
	"aaagffggbafdgfdebbcccecdeed",
	"aaafggfgbaddffgebbddcecceec",
	"aaagfdggdabdgfdeffbbcecceec",
	"aaafgdfgdabdffdeggbbcecceec",
	"aaaeggeegabdfddedgbbcfccffc",
	"aaagcdcccabdggdegfbbdeffeef",
	"aaaecdcccabdeedegfbbdgffggf",
	"aaafddffcabgddcefcbbgeggeec",
	"aaaggdcccabdgfdgcebbdffefee",
	"aaaffefeeagdggdfbecccgcdbbd",
	"aaaggegeeaffdgfdbedfcdccbbc",
	"aaaecdcccafgeedebdffgfggbbd",
	"aaaeddddcafgeecebcffgfggbbc",
	"aaaeddeecafgddcebcffgfggbbc",
	"aaaggegeeacdfgdfbecccffdbbd",
	"aaaggegeeaddfgcfbeddcffcbbc",
	"aaagbegeeabdfbdggecccfcdffd",
	"aaagbfggfabdgbdeffcccecdeed",
	"aaaebdeedabdfbdeggcccfcgffg",
	"aaagbdggdabdgbdffecccfcefee",
	"aaaggdbgdafdbfdbgecffccecee",
	"aaaeedbedacdbedbgfcccgffggf",
	"aaaggdbgdacdbfdbgecccffefee",
	"aaaddebddacebeebgfcccgffggf",
	"aaaddebeeafgbddbceffgfggccc",
	"aaaddebddafgbeebceffgfggccc",
	"aaageegebaddfebggbddcfccffc",
	"aaaeggeebaddfgbegbddcfccffc",
	"aaagffggbafegfbddbceeccecdd",
	"aaaeddddbafgeebecbffgfggccc",
	"aaaeddeebafgddbecbffgfggccc",
	"aaaffgfggadebddfgdbeebceccc",
	"aaaefdeedagdbfdeffbggbcgccc",
	"aaaffdfedagdbedfeebggbcgccc",
	"aaaffgfggaeebedfgdbedbcdccc",
	"aaaffefeeagdbddfdebggbcgccc",
	"aaaeffeecafgbfgeccbggbddddc",
	"aaaeggeecafgbfgeccbffbddddc",
	"aaaddfcddaffbgfccebggbgecee",
	"aaaddgcddagfbggccebffbfecee",
	"aaaggdcccagebgdfcdbeebfeffd",
	"aaaeffeefaggbfdecdbgdbgdccc",
	"aaaeffeefaggbfceddbgcbgcddc",
	"aaafggffgaddeebefgddbecbccc",
	"aaaeggeegaddffbefgddbfcbccc",
	"aaafggffgaeedebdfgdebdcbccc",
	"aaaggegeeaddfgbfceddbffbccc",
	"aaaffefeeacdggdfbecccgbdgbd",
	"aaaeggeegafdcfdebgcffcbdcbd",
	"aaaffefeeaddggcfbeddcgbcgbc",
	"aaagbegeeaddfbbggeddcfccffc",
	"aaagbfggfaddgbbeffddcecceec",
	"aaaggebeeagdfgdbbecccfcdffd",
	"aaaddfbddaffggfbbecccgcegee",
	"aaaddebeeaffgddbbeggfgcfccc",
	"aaaddebddaffgeebbeggfgcfccc",
	"aaaddfbddaffcgfbbecggcgecee",
	"aaaddgbddagfcggbbecffcfecee",
	"aaafggffgabedeedfgdbbdceccc",
	"aaaffefeeabdggdfgecbbccdcgd",
	"aaaggegeeabdfgdffecbbccdcfd",
	"aaafggfddabgffgddecbbccecee",
	"aaaeggeecabgffgeccfbbfddddc",
	"aaaffdcfdabdfgdccegbbggecee",
	"aaaggegeeabfdgfdcedbbdffccc",
	"aaaggegeeabfcgfddecbbcffcdd",
	"aaaeggeegacdbfdefgcccbbdffd",
	"aaaffefeeaddbggfceddgbbgccc",
	"aaaeggeegaddbfcefgddcbbcffc",
	"aaadcecccafgdeedbeffgfggdbb",
	"aaaeggeegaddddfebgcffccfcbb",
	"aaaddeceeafgcddcbeffgfggcbb",
	"aaaddecddafgceecbeffgfggcbb",
	"aaaeffeefaggcfdebdcgdcgdcbb",
	"fbbfbeaaaffegeeaddggcgccddc",
	"gbbgbfaaaeffggfaddeececcddc",
	"fbbfbdaaaffeggdagdceeccecgd",
	"ggfgffaaadgfdbbabecccdcedee",
	"cddddeaaaccefeeaggcbbfbgffg",
	"ceeddeaaaccefddaggcbbfbgffg",
	"geeggeaaagdecddafdcbbcbfcff",
	"eedegdaaaeggcgdafdcbbcbfcff",
	"gedggdaaageecedafdcbbcbfcff",
	"gffggfaaagfdcedaeecbbcbdced",
	"gffggfaaagfdcddadecbbcbecee",
	"cfdffdaaacfecgdagdceebbebgg",
	"cccdffaaadcedgfagfdeebbebgg",
	"cccdggaaadcedgfagfdeebbebff",
	"eefeffaaaecfddgaddcccbbgbgg",
	"bbdgbdaaaeffggdagdeefecfccc",
	"bbdebdaaaefgeedacdffgfggccc",
	"bbdfbdaaaefgffdacdeegeggccc",
	"ffgfggaaaebbfgbaddeececcddc",
	"geeggeaaagfebbdabdffdfcdccc",
	"ggfgffaaaegfbbdabdeedecdccc",
	"cccecdaaaeffeedagdbbfgbfggd",
	"eefeffaaaegfggdacdbbdgbdccc",
	"ggfgffaaaegfeedacdbbdebdccc",
	"ggfgffaaadgfdecaeebbcdbcdec",
	"eefeffaaaegfggcaddbbcgbcddc",
	"ggfgffaaaegfeecaddbbcebcddc",
	"eeceffaaaefcgfcaddggcgbbddb",
	"fecfeeaaaffcgecaddggcgbbddb",
	"gfcgffaaaeccggfaddeecebbddb",
	"feeffeaaadcedfgaggcccdbbdgb",
	"feeffeaaaddecfgaggcddcbbcgb",
	"gdbgbbaaaeddggfaffeedecfccc",
	"ggbgbbaaadgeddfadfceeccecff",
	"eebebbaaaecdfgdaggcccfgdffd",
	"eebebbaaaecdggdaffcccgfdgfd",
	"ffbfbbaaaedgfddacdeegeggccc",
	"eebebbaaaeffgfdacdggdgfdccc",
	"eebebbaaaeggffdacdfgdfgdccc",
	"eebebbaaaeddfgcaggddcfgcffc",
	"eebebbaaaeddggcaffddcgfcgfc",
	"eebebbaaaeffgfcaddggcgfcddc",
	"eebebbaaaeggffcaddfgcfgcddc",
	"eegeggaaaeddfgbabbddcfccffc",
	"eefeffaaaedfgddacdggbgbbccc",
	"ffdfgdaaaeggfgdacdeebebbccc",
	"gfdgfdaaaeffggdacdeebebbccc",
	"eedeffaaaeddcgfagfcdbcbbcgg",
	"eedeggaaaeddcgfagfcdbcbbcff",
	"cccgcdaaaeffggdagdeefebfbbd",
	"cccecdaaaefdeedaggffdfbgbbg",
	"cccfcdaaaefdffdaggeedebgbbg",
	"eeceddaaaefcddcaggffcfbgbbg",
	"ddceddaaaefceecaggffcfbgbbg",
	"ddcfddaaaefcffcaggeecebgbbg",
	"geeggeaaagfeddcaddffcfbcbbc",
	"ggfgffaaaegfddcaddeecebcbbc",
	"bddbbeaaaddefeeaggcccfcgffg",
	"beebbeaaaddefddaggcccfcgffg",
	"beebbeaaafdefddagdffcgccggc",
	"bedbbdaaafeefedagdffcgccggc",
	"bddbbgaaaddeffgaggfeefceccc",
	"beebbeaaaggeddfaddgffgcfccc",
	"bggbbgaaaeffddgaddeefecfccc",
	"beebbeaaadgeddfadfcggccgcff",
	"bffbbfaaadfgddgadecggccecee",
	"bfdbbdaaaffefgdagdceeccecgg",
	"beebbeaaagcegffaddcccggfddf",
	"bgdbbdaaafgeggdacdfeeffeccc",
	"bfdbbdaaaffefgdacdgeeggeccc",
	"beebbeaaaddeffgacgfddfggccc",
	"bddbbgaaaddecfgaggceecfecff",
	"bddbbfaaaddecffafgceecgecgg",
	"beebbeaaaffecgdagdcfdcfdcgg",
	"beebbeaaadgedgcaffggcdfcdfc",
	"eefeffaaaebfgbbaddggcgccddc",
	"cccgcdaaaggegfdafdbeebbeffd",
	"gddgffaaaddeggfacfbeebbeccc",
	"geeggeaaagfeffdacdbfdbbdccc",
	"feeffeaaaggegfdacdbgdbbdccc",
	"geeggeaaagfeffcaddbfcbbcddc",
	"feeffeaaaggegfcaddbgcbbcddc",
	"fddffgaaaddecfgaggceecbecbb",
	"gbdgbdaaafbeggdacdfeeffeccc",
	"ggfgffaaabgfbeeacebddddeccc",
	"feeffeaaabgebfdacdbgdggdccc",
	"ggfgffaaabgfbedacdbedeedccc",
	"feeffeaaabgebfcaddbgcggcddc",
	"ggfgffaaabgfbecaddbeceecddc",
	"ggfgffaaabgfbecaeebdcddcdec",
	"gffggfaaagfbcebaeecdbcddced",
	"gffggfaaagfbcdbadecdbcdecee",
	"bbfgffaaaebfggdagdeedecdccc",
	"bbdffdaaafbefgdagdceeccecgg",
	"bbdffdaaafbefgdacdgeeggeccc",
	"eefebbaaaeffgfbaddggcgccddc",
	"eecebbaaaeccgfbaffggcgddddf",
	"ffcfbbaaaeccfgbaddeeceggddg",
	"cggffgaaacbbcfgafecdbddedee",
	"geeggeaaagfebbdacdffdfbdccc",
	"ggfgffaaaegfbbdacdeedebdccc",
	"geeggeaaagfebbcaddffcfbcddc",
	"ggfgffaaaegfbbcaddeecebcddc",
	"eegedgaaaeggfddabbcccfcdffb",
	"eeceffaaaefcgfcabbggcgddddb",
	"fecfeeaaaffcgecabbggcgddddb",
	"gfcgffaaaeccggfabbeeceddddb",
	"geeggeaaagdecdfabbcffcdfcdb",
	"eegeggaaaeffcgfabbcfdcddcdb",
	"eefeffaaaegfcggabbcgdcddcdb",
	"bdgbggaaaeddbgfaffeedecfccc",
	"bddbffaaaddebgfagfceeccecgg",
	"bddbggaaaddebgfagfceeccecff",
	"beebgeaaaddebggafgcddccfcff",
	"beebfeaaaddebfgaffcddccgcgg",
	"bggbgeaaaddgbeeafecddccfcff",
	"bggbgfaaaddgbffafecddccecee",
	"bffbggaaaddfbgfagecddccecee",
	"bgcbggaaaegcbfcaffeeceddddf",
	"bfcbffaaaeccbgfaddeeceggddg",
	"bddbffaaaddebgfacfgeeggeccc",
	"ffbfgbaaaeggfgbaddeececcddc",
	"gfbgfbaaaeffggbaddeececcddc",
	"fdbfdbaaaffecdbadgceecgecgg",
	"eefeffaaaebfgbdacdggdgbdccc",
	"eefeffaaaebfgbcaddggcgbcddc",
	"ffcfggaaaeccfgbagbeeceddddb",
	"eeceggaaaeccfgbagbddcfddffb",
	"geeggeaaagceffbafbcccfddddb",
	"feeffeaaadcedfbagbcccdggdgb",
	"eefeffaaaecfddbagbcccgddggb",
	"feeffeaaaddecfbagbcddcggcgb",
	"cccbbdaaaecgbfdafdeegeggffd",
	"ffdbbdaaaefgbfdacdeegeggccc",
	"ffcfggaaabbcfgcagebdcddedee",
	"bfdffdaaabfebgdagdceeccecgg",
	"bddddeaaabcebeeagfcccgffggf",
	"beeddeaaabcebddagfcccgffggf",
	"bddddeaaabfgbeeaceffgfggccc",
	"bedeedaaabfgbedacdffgfggccc",
	"bfdffdaaabfebgdacdgeeggeccc",
	"eebeffaaaefbgfbaddggcgccddc",
	"febfeeaaaffbgebaddggcgccddc",
	"ffbfggaaaddbfgbagecddccecee",
	"eebeddaaaecbddbagfcccgffggf",
	"ddbeddaaaecbeebagfcccgffggf",
	"eedebdaaaeffgbdabdggfgcfccc",
	"ffdfbdaaaggefbdabdgeegceccc",
	"feefbeaaaffegbdabdggdgcdccc",
	"ffgfbgaaaeggfbdabdeedecdccc",
	"geeggeaaagbeffdacdfbdfbdccc",
	"eefeffaaaebfcgdagdcbdcbdcgg",
	"geeggeaaagbeffcaddfbcfbcddc",
	"geeggeaaagdebddafdcccbcfbff",
	"eedegdaaaeggbgdafdcccbcfbff",
	"gedggdaaageebedafdcccbcfbff",
	"gffggfaaagfdbedaeecccbcdbed",
	"gffggfaaagfdbddadecccbcebee",
	"eeceffaaaeccbgfagfddcbddbgg",
	"eeceggaaaeccbgfagfddcbddbff",
	"cddddgaaaccebfgaggceebfebff",
	"cddddfaaaccebffafgceebgebgg",
	"cccffdaaagcdbfdafeggdbgebee",
	"eegeggaaaecdbgdaffcccbfdbfd",
	"eegeggaaaeddbgcaffddcbfcbfc",
	"ggfgffaaadgfdebaeecccdcbdeb",
	"eefeffaaaegfggbaddcccgcbddb",
	"ggfgffaaaegfeebaddcccecbddb",
	"feeffeaaagcegfbaddcccggbddb",
	"gfbgffaaaebbggfaddeececcddc",
	"ffbfggaaaebbfgdagdeedecdccc",
	"eedebdaaaefgbbdacdffgfggccc",
	"ggdgbdaaafgebbdacdfeeffeccc",
	"cccecdaaaebdeedagfbbdgffggf",
	"feeffeaaadbedfgaggbbcdccdgc",
	"geeggeaaagbeffdafdbbdfcdccc",
	"eeceddaaaebcddcagfbbcgffggf",
	"ddceddaaaebceecagfbbcgffggf",
	"feeffeaaagbegfdacdbbdggdccc",
	"feeffeaaagbegfcaddbbcggcddc",
	"cccecdaaaefgeedabdffgfggbbd",
	"cccfcdaaaefgffdabdeegeggbbd",
	"eefeffaaaedfgddabdggcgccbbc",
	"ffdfgdaaaeggfgdabdeececcbbc",
	"gfdgfdaaaeffggdabdeececcbbc",
	"ggcgddaaaegcddcabfeeceffbbf",
	"cccffdaaafcefgdabdgeeggebbd",
	"ffdfbdaaaebgfbdacdeegeggccc",
	"eegeggaaaeffbgfaddbfcbccddc",
	"eefeffaaaegfbggaddbgcbccddc",
	"fddffgaaaddebfgaggbeebceccc",
	"feeffeaaaddebfgacgbddbggccc",
	"geeggeaaagfeddbaddffbfcbccc",
	"ggfgffaaaegfddbaddeebecbccc",
	"deeffeaaaddecfbafgcdbcgbcgg",
	"bddddeaaabbefeeaggcccfcgffg",
	"beeddeaaabbefddaggcccfcgffg",
	"bddddgaaabbeffgaggfeefceccc",
	"beeffeaaabbegfdafdggdgcdccc",
	"bddddgaaabbecfgaggceecfecff",
	"bddddfaaabbecffafgceecgecgg",
	"feefbeaaaffegbbaddggcgccddc",
	"ffgfbgaaaeggfbbaddeececcddc",
	"cccdceaaadbedeeagfdbbgffggf",
	"eefeffaaaebfddgaddcbbccgcgg",
	"cddddeaaacbeceeagfcbbgffggf",
	"ceeddeaaacbecddagfcbbgffggf",
	"eegeggaaaebdcgdaffcbbcfdcfd",
	"geeggeaaagcebffaddcccbbfddf",
	"eefeffaaaegfbgdacdggdbbdccc",
	"eefeffaaaegfbgcaddggcbbcddc",
	"ggfgffaaadgfdeeabecccdcedbb",
	"gddgffaaaddeggfabfceeccecbb",
	"geeggeaaagfeffdabdcfdccdcbb",
	"feeffeaaaggegfdabdcgdccdcbb",
	"eeceffaaaeccggfabfddcgddgbb",
	"cgdggdaaaccegfdabdceeffefbb",
	"feeffeaaadcedfgabgcccdggdbb",
	"feeffeaaaddecfgabgcddcggcbb",
	"gbbgbfcffaaaggfcceaddddecee",
	"gbbgbeceeaaaggfcceaffddfcdd",
	"cbbcbfcffaaacgfggeaddddegee",
	"cbbcbeceeaaacgfggeaffddfgdd",
	"ffcfbcbbcaaafgcggeaddddegee",
	"bggbbgcffaaacfgcfeaddddecee",
	"bggbbgcccaaaffgfceaddddefee",
	"cccbcfbffaaabgfggeaddddegee",
	"cccbcebeeaaabgfggeaffddfgdd",
	"bffbfeceeaaabfgcceaddddgcgg",
	"ffbfcbcccaaafgbggeaddddegee",
	"ffbfgbcggaaafgbcceaddddecee",
	"cccfcgffgaaabggbfeaddddebee",
	"cggccgcffaaabfgbfeaddddebee",
	"fggffgcccaaabfgbceaddddebee",
	"ggcfgcffcaaabgcbfeaddddebee",
	"cggccgcbbaaaffgfbeaddddefee",
	"fggffgcbbaaacfgcbeaddddecee",
	"cccfcefeeaaaffgbbeaddddgbgg",
	"cffcfeceeaaacfgbbeaddddgbgg",
	"ffcfccddcaaafgbeddaggegbeeb",
	"cggbbfbffcgecgfaaaceeddeadd",
	"cccbbfbffgceggfaaageeddeadd",
	"bbcgbcggcffegfcaaafeeddeadd",
	"ceefbefbbcceffgaaacddddgagg",
	"cggfbgfbbcceffgaaaceeddeadd",
	"ceecbecbbffecfgaaafddddgagg",
	"cggcbgcbbffecfgaaafeeddeadd",
	"ceebgebggccebgfaaacffddfadd",
	"cccgcbggbffegfbaaafeeddeadd",
	"cffgfbggbccegfbaaaceeddeadd",
	"ggfgcfcccbgebffaaabeeddeadd",
	"cggccfcffbgebgfaaabeeddeadd",
	"cccggfgffbcebgfaaabeeddeadd",
	"ggcgfcffcbgebfcaaabeeddeadd",
	"beebcecccffebfgaaafddddgagg",
	"bggbcgcccffebfgaaafeeddeadd",
	"cbbccfcffgbeggfaaageeddeadd",
	"cbbggfgffcbecgfaaaceeddeadd",
	"geegcecccbbeggfaaabffddfadd",
	"ceecgecggbbecgfaaabffddfadd",
	"ddcgccggceddgfbaaaeebefbaff",
}};

std::map<std::string, int> init_key_map;

int rotate_scheme[24][3] = {
	{0, 0, 0},
	{1, 0, 0},
	{2, 0, 0},
	{3, 0, 0},
	{0, 1, 0},
	{1, 1, 0},
	{2, 1, 0},
	{3, 1, 0},
	{0, 2, 0},
	{1, 2, 0},
	{2, 2, 0},
	{3, 2, 0},
	{0, 3, 0},
	{1, 3, 0},
	{2, 3, 0},
	{3, 3, 0},
	{0, 0, 1},
	{1, 0, 1},
	{2, 0, 1},
	{3, 0, 1},
	{0, 0, 3},
	{1, 0, 3},
	{2, 0, 3},
	{3, 0, 3}
};

void init()
{
	init_key_map["aaa......a................."] = 0;
	init_key_map["a..a..a..a................."] = 1;
	init_key_map["aaa........a..............."] = 2;
	init_key_map["a..a..a........a..........."] = 3;
	init_key_map["aa........a........a......."] = 4;
	init_key_map["a..a........a........a....."] = 5;
	init_key_map["aa.......a........a........"] = 6;
	init_key_map["a..a.....a........a........"] = 7;
	init_key_map["..a......aaa..............."] = 8;
	init_key_map["......a..a..a..a..........."] = 9;
	init_key_map["a........aaa..............."] = 10;
	init_key_map["a........a..a..a..........."] = 11;
	init_key_map["a........a........aa......."] = 12;
	init_key_map["a........a........a..a....."] = 13;
	init_key_map[".a........a.......aa......."] = 14;
	init_key_map["...a........a.....a..a....."] = 15;
	init_key_map["aaaa......................."] = 16;
	init_key_map["aa..a..a..................."] = 17;
	init_key_map["..aaaa....................."] = 18;
	init_key_map["a..a..aa..................."] = 19;
	init_key_map["a..aaa....................."] = 20;
	init_key_map["aa.a..a...................."] = 21;
	init_key_map["aaa..a....................."] = 22;
	init_key_map[".a..a.aa..................."] = 23;
}

int find_init_idx(char input[])
{
	int i, j, k, c, min_l, min_r, min_c;
	min_l = min_r = min_c = 3;
	for(c = i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++)
			{
				if(input[c] == 'a')
				{
					if(i < min_l)
						min_l = i;
					if(j < min_r)
						min_r = j;
					if(k < min_c)
						min_c = k;
				}
				c++;
			}
	if(min_l > 0)
		for(i = 0; i < 28; i++)
			if(input[i] == 'a')
			{
				input[i] = '.';
				input[i-9*min_l] = 'a';
			}
	if(min_r > 0)
		for(i = 0; i < 28; i++)
			if(input[i] == 'a')
			{
				input[i] = '.';
				input[i-3*min_r] = 'a';
			}
	if(min_c > 0)
		for(i = 0; i < 28; i++)
			if(input[i] == 'a')
			{
				input[i] = '.';
				input[i-min_c] = 'a';
			}
	return init_key_map[input];
}

void rotate_all_result(int idx)
{
	int i, r;
	char t0, t1, t2;
	memcpy(result[idx], result[0], sizeof(result[0]));
	for(r = 0; r < result_num; r++)
	{
		for(i = 0; i < rotate_scheme[idx][2]; i++)
		{
			t0 = result[idx][r][0], t1 = result[idx][r][1], t2 = result[idx][r][2];
			result[idx][r][0] = result[idx][r][6], result[idx][r][1] = result[idx][r][7], result[idx][r][2] = result[idx][r][8];
			result[idx][r][6] = result[idx][r][24], result[idx][r][7] = result[idx][r][25], result[idx][r][8] = result[idx][r][26];
			result[idx][r][24] = result[idx][r][18], result[idx][r][25] = result[idx][r][19], result[idx][r][26] = result[idx][r][20];
			result[idx][r][18] = t0, result[idx][r][19] = t1, result[idx][r][20] = t2;
			t0 = result[idx][r][3], t1 = result[idx][r][4], t2 = result[idx][r][5];
			result[idx][r][3] = result[idx][r][15], result[idx][r][4] = result[idx][r][16], result[idx][r][5] = result[idx][r][17];
			result[idx][r][15] = result[idx][r][21], result[idx][r][16] = result[idx][r][22], result[idx][r][17] = result[idx][r][23];
			result[idx][r][21] = result[idx][r][9], result[idx][r][22] = result[idx][r][10], result[idx][r][23] = result[idx][r][11];
			result[idx][r][9] = t0, result[idx][r][10] = t1, result[idx][r][11] = t2;
		}
		for(i = 0; i < rotate_scheme[idx][1]; i++)
		{
			t0 = result[idx][r][0], t1 = result[idx][r][3], t2 = result[idx][r][6];
			result[idx][r][0] = result[idx][r][18], result[idx][r][3] = result[idx][r][21], result[idx][r][6] = result[idx][r][24];
			result[idx][r][18] = result[idx][r][20], result[idx][r][21] = result[idx][r][23], result[idx][r][24] = result[idx][r][26];
			result[idx][r][20] = result[idx][r][2], result[idx][r][23] = result[idx][r][5], result[idx][r][26] = result[idx][r][8];
			result[idx][r][2] = t0, result[idx][r][5] = t1, result[idx][r][8] = t2;
			t0 = result[idx][r][1], t1 = result[idx][r][4], t2 = result[idx][r][7];
			result[idx][r][1] = result[idx][r][9], result[idx][r][4] = result[idx][r][12], result[idx][r][7] = result[idx][r][15];
			result[idx][r][9] = result[idx][r][19], result[idx][r][12] = result[idx][r][22], result[idx][r][15] = result[idx][r][25];
			result[idx][r][19] = result[idx][r][11], result[idx][r][22] = result[idx][r][14], result[idx][r][25] = result[idx][r][17];
			result[idx][r][11] = t0, result[idx][r][14] = t1, result[idx][r][17] = t2;
		}
		for(i = 0; i < rotate_scheme[idx][0]; i++)
		{
			t0 = result[idx][r][0], t1 = result[idx][r][9], t2 = result[idx][r][18];
			result[idx][r][0] = result[idx][r][6], result[idx][r][9] = result[idx][r][15], result[idx][r][18] = result[idx][r][24];
			result[idx][r][6] = result[idx][r][8], result[idx][r][15] = result[idx][r][17], result[idx][r][24] = result[idx][r][26];
			result[idx][r][8] = result[idx][r][2], result[idx][r][17] = result[idx][r][11], result[idx][r][26] = result[idx][r][20];
			result[idx][r][2] = t0, result[idx][r][11] = t1, result[idx][r][20] = t2;
			t0 = result[idx][r][1], t1 = result[idx][r][10], t2 = result[idx][r][19];
			result[idx][r][1] = result[idx][r][3], result[idx][r][10] = result[idx][r][12], result[idx][r][19] = result[idx][r][21];
			result[idx][r][3] = result[idx][r][7], result[idx][r][12] = result[idx][r][16], result[idx][r][21] = result[idx][r][25];
			result[idx][r][7] = result[idx][r][5], result[idx][r][16] = result[idx][r][14], result[idx][r][25] = result[idx][r][23];
			result[idx][r][5] = t0, result[idx][r][14] = t1, result[idx][r][23] = t2;
		}
	}
}

int main()
{
	char input[28];
	valid_result[0] = true;
	init();
	while(scanf("%s", input) != EOF)
	{
		int idx = find_init_idx(input);
		if(!valid_result[idx])
		{
			rotate_all_result(idx);
			valid_result[idx] = true;
		}
		for(int i = 0; i < result_num; i++)
			printf("%s\n", result[idx][i]);
		printf("\n");
	}
	return 0;
}