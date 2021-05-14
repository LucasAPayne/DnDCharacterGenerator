#pragma once

#include "Types.h"

#include <string>
#include <unordered_map>
#include <utility> // std::pair
#include <vector>

namespace dnd {

	// ======================================================================================
	// Small Lists
	// ======================================================================================

	const std::vector<std::string> Classes = {
		"Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"
	};

	const std::vector<std::string> Races = {
		"Hill Dwarf", "Mountain Dwarf", "High Elf", "Wood Elf", "Dark Elf (Drow)", "Lightfoot Halfling", "Stout Halfling", "Human", "Dragonborn",
		"Forest Gnome", "Rock Gnome", "Half-Elf", "Half-Orc", "Tiefling"
	};

	const std::vector<std::string> Ethnicities = {
		"Calishite", "Chondathan", "Damaran", "Illuskan", "Mulan", "Rashemi", "Shou", "Tethyrian", "Turami"
	};

	const std::vector<std::string> Genders = {
		"Male", "Female"
	};

	// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
	const std::vector<std::string> Backgrounds = {
		"Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan", "Guild Merchant", "Hermit", "Knight",
		"Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier", "Spy", "Urchin"
	};

	const std::vector<std::string> Alignments = {
		"Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral", "Lawful Evil", "Neutral Evil", "Chaotic Evil"
	};

	// Common is not a possible language because every character already knows it
	const std::vector<std::string> Languages = {
		"Elvish", "Dwarvish", "Giant", "Gnomish", "Goblin", "Halfling", "Orc",                               // Common Languages
		"Abyssal", "Celestial", "Draconic", "Deep Speech", "Infernal", "Primordial", "Sylvan", "Undercommon" // Exotic Languages
	};

	// First entry null so that expForLevel[1] is how much exp is required for level one, etc.
	const std::vector<int> ExpForLevel = {
		 NULL, 0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000
	};

	// ======================================================================================
	// Equipment
	// ======================================================================================

	const std::vector<std::string> ArmorTypes = {
		"light armor", "medium armor", "heavy armor", "shield"
	};

	// Maps armor to its armor class 
	const std::unordered_map<std::string, int> LightArmorClasses = {
		{"padded armor", 11},
		{"leather armor", 11},
		{"studded leather armor", 12},
	};

	const std::unordered_map<std::string, int> MediumArmorClasses = {
		{"hide armor", 12},
		{"chain shirt", 13},
		{"scale mail", 14},
		{"breastplate", 14},
		{"half plate", 15},
	};

	const std::unordered_map<std::string, int> HeavyArmorClasses = {
		{"ring mail", 14},
		{"chain mail", 16},
		{"splint armor", 17},
		{"plate armor", 18}
	};

	const std::vector<std::string> SimpleMeleeWeapons = {
		"club", "dagger", "greatclub", "handaxe", "javelin", "light hammer", "mace", "quarterstaff", "sickle", "spear"
	};

	const std::vector<std::string> SimpleRangedWeapons = {
		"light crossbow", "dart", "shortbow", "sling"
	};
	const std::vector<std::string> MartialMeleeWeapons = {
		"battleaxe", "flail", "glaive", "greataxe", "greatsword", "halberd", "lance", "longsword", "maul", "morningstar", "pike",
		"rapier", "scimitar", "shortsword", "trident", "war pick", "warhammer", "whip"
	};

	const std::vector<std::string> MartialRangedWeapons = {
		"blowgun", "hand crossbow", "heavy crossbow", "longbow", "net"
	};

	const std::vector<std::string> AllSimpleWeapons = { 
		"club", "dagger", "greatclub", "handaxe", "javelin", "light hammer", "mace", "quarterstaff", "sickle", "spear",
		"light crossbow", "dart", "shortbow", "sling" 
	};

	const std::vector<std::string> AllMartialWeapons = {
		"battleaxe", "flail", "glaive", "greataxe", "greatsword", "halberd", "lance", "longsword", "maul", "morningstar", "pike", 
		"rapier", "scimitar", "shortsword", "trident", "war pick", "warhammer", "whip",
		"blowgun", "hand crossbow", "heavy crossbow", "longbow", "net"
	};

	const std::unordered_map<std::string, std::string> WeaponAttacks = {
		{"club", "1d4 bludgeoning"},
		{"dagger", "1d4 piercing"},
		{"greatclub", "1d8 bludgeoning"},
		{"handaxe", "1d6 slashing"},
		{"javelin", "1d6 piercing"},
		{"light hammer", "1d4 bludgeoning"},
		{"mace", "1d6 bludgeoning"},
		{"quarterstaff", "1d6 bludgeoning"},
		{"sickle", "1d4 slashing"},
		{"spear", "1d6 piercing"},
		{"light crossbow", "1d8 piercing"},
		{"dart", "1d4 piercing"},
		{"shortbow", "1d6 piercing"},
		{"sling", "1d4 bludgeoning"},
		{"battleaxe", "1d8 slashing"},
		{"flail", "1d8 bludeoning"},
		{"glaive", "1d10 slashing"},
		{"greataxe", "1d12 slashing"},
		{"greatsword", "2d6 slashing"},
		{"halberd", "1d10 slashing"},
		{"lance", "1d12 piercing"},
		{"longsword", "1d8 slashing"},
		{"maul", "2d6 bludgeoning"},
		{"morningstar", "1d8 piercing"},
		{"pike", "1d10 piercing"},
		{"rapier", "1d8 piercing"},
		{"scimitar", "1d6 slashing"},
		{"shortsword", "1d6 piercing"},
		{"trident", "1d6 piercing"},
		{"war pick", "1d8 slashing"},
		{"warhammer", "1d8 bludgeoning"},
		{"whip", "1d4 slashing"},
		{"blowgun", "1 piercing"},
		{"hand crossbow", "1d6 piercing"},
		{"heavy crossbow", "1d10 piercing"},
		{"longbow", "1d8 piercing"},
		{"net", ""}
	};

	// Map the types of draconic ancestry for dragonborn to the damage type of the breath weapon
	const std::unordered_map<std::string, std::string> BreathWeaponTypes = {
		{"black", "acid"},
		{"blue", "lightning"},
		{"brass", "fire"},
		{"bronze", "lightning"},
		{"copper", "acid"},
		{"gold", "fire"},
		{"green", "poison"},
		{"red", "fire"},
		{"silver", "cold"},
		{"white", "cold"}
	};

	const std::vector<std::string> ArtisanTools = {
		"alchemist's supplies", "brewer's supplies", "calligrapher's supplies", "carpenter's tools", "cobbler's tools", "cook's utensils", "glassblower's tools",
		"jeweler's tools", "leatherworker's tools", "mason's tools", "painter's supplies", "potter's tools", "smith's tools", "tinker's tools", "weaver's tools", "woodcarver's tools"
	};

	const std::vector<std::string> GamingSets = {
		"dice set", "Dragonchess set", "playing card set", "Three-Dragon Ante set"
	};

	const std::vector<std::string> MusicalInstruments = {
		"bagpipes", "drum", "dulcimer", "flute", "lute", "lyre", "horn", "pan flute", "shawm", "viol"
	};

	const std::vector<std::string> OtherTools = {
		"disguise kit", "forgery kit", "herbalism kit", "navigator's tools", "poisoner's kit", "thieves' tools", "vehicles (land)", "vehicles (water)"
	};

	const std::vector<std::string> Trinkets = {
		"mummified goblin hand",
		"piece of crystal that faintly glows in the moonlight",
		"gold coin minted in an unknown land",
		"diary written in a language you don't know",
		"brass ring that never tarnishes",
		"old chess piece made from glass",
		"pair of knucklebone dice, each with a skull symbol on the side that would normally show six pips",
		"small idol depicting a nightmarish creature that gives you unsettling dreams when you sleep near it",
		"rope necklace from which dangles four mummified elf fingers",
		"the deed for a parcel of land in a realm unknown to you",
		"1-ounce block made from an unknown material",
		"small cloth doll skewered with needles",
		"tooth from an unknown beast",
		"enormous scale, perhaps from a dragon",
		"bright green feather",
		"old divination card bearing your likeness",
		"glass orb filled with moving smoke",
		"1-pound egg with a bright red shell",
		"pipe that blows bubbles",
		"glass jar containing a weird bit of flesh floating in pickling fluid",
		"tiny gnome-crafted music box that plays a song you dimly remember from your childhood",
		"small wooden statuette of a smug halfling",
		"brass orb etched with strange runes",
		"multicolored stone disk",
		"tiny silver icon of a raven",
		"bag containing forty-seven humanoid teeth, one of which is rotten",
		"shard of obsidian that always feels warm to the touch",
		"dragon's bony talon hanging from a plain leather necklace",
		"pair of old socks",
		"blank book whose pages refuse to hold ink, chalk, graphite, or any other substance or marking",
		"silver badge in the shape of a five-pointed star",
		"knife that belonged to a relative",
		"glass vial filled with nail clippings",
		"rectangular metal device with two tiny metal cups on one end that throws sparks when wet",
		"white, sequined glove sized for a human",
		"vest with one hundred tiny pockets",
		"small, weightless stone block",
		"tiny sketch portrait of a goblin",
		"empty glass vial that smells of perfume when opened",
		"gemstone that looks like a lump of coal when examined by anyone but you",
		"scrap of cloth from an old banner",
		"rank insignia from a lost legionnaire",
		"tiny silver bell without a clapper",
		"mechanical canary inside a gnomish lamp",
		"tiny chest carved to look like it has numerous feet on the bottom",
		"dead sprite inside a clear glass bottle",
		"metal can that has no opening but sounds as if it is filled with liquid, sand, spiders, or broken glass (your choice)",
		"glass orb filled with water, in which swims a clockwork goldfish",
		"silver spoon with an M engraved on the handle",
		"whistle made from gold-colored wood",
		"dead scarab beetle the size of your hand",
		"two toy soldiers, one with a missing head",
		"small box filled with different-sized buttons",
		"candle that can't be lit",
		"tiny cage with no door",
		"old key",
		"indecipherable treasure map",
		"hilt from a broken sword",
		"rabbit's foot",
		"glass eye",
		"cameo carved in the likeness of a hideous person",
		"silver skull the size of a coin",
		"alabaster mask",
		"pyramid of sticky black incense that smells very bad",
		"nightcap that, when worn, gives you pleasant dreams",
		"single caltrop made from bone",
		"gold monocle frame without the lens",
		"1-inch cube, each side painted a different color",
		"crystal knob from a door",
		"small packet filled with pink dust",
		"fragment of a beautiful song, written as musical notes on two pieces of parchment",
		"silver teardrop earring made from a real teardrop",
		"the shell of an egg painted with scenes of human misery in disturbing detail",
		"fan that, when unfolded, shows a sleeping cat",
		"set of bone pipes",
		"four-leaf clover pressed inside a book discussing manners and etiquette",
		"sheet of parchment upon which is drawn a complex mechanical contraption",
		"ornate scabbard that fits no blade you have found so far",
		"invitation to a party where a murder happened",
		"bronze pentacle with an etching of a rat's head in its center",
		"purple handkerchief embroidered with the name of a powerful archmage",
		"half of a floorplan for a temple, castle, or some other structure",
		"bit of folded cloth that, when unfolded, turns into a stylish cap",
		"receipt of deposit at a bank in a far-flung city",
		"diary with seven missing pages",
		"empty silver snuffbox bearing an inscription on the surface that says \"dreams\"",
		"iron holy symbol devoted to an unknown god",
		"book that tells the story of a legendary hero's rise and fall, with the last chapter missing",
		"vial of dragon blood",
		"ancient arrow of elven design",
		"needle that never bends",
		"ornate brooch of dwarven design",
		"empty wine bottle bearing a pretty label that says, \"The Wizard of Wines Winery, Red Dragon Crush, 331422-W\"",
		"mosaic tile with a multicolored, glazed surface",
		"petrified mouse",
		"black pirate flag adorned with a dragon's skull and crossbones",
		"tiny mechanical crab or spider that moves about when it's no longer being observed",
		"glass jar containing lard with a label that reads, \"Griffon Grease\"",
		"wooden box with a ceramic bottom that holds a living worm with a head on each end of its body",
		"metal urn containing the ashes of a hero"
	};

	// ======================================================================================
	// Non-human Names
	// ======================================================================================

	const std::unordered_map<std::string, const std::vector<std::string>> NonHumanSurnames = {
		{"Dwarf", {
			"Balderk", "Battlehammer", "Brawnanvil", "Dankil", "Fireforge", "Frostbeard", "Forunn", "Holderhek", "Ironfist", "Loderr",
			"Lutgehr", "Rumnaheim", "Strakein", "Torunn", "Ungart"
		}},

		{"Elf", {
			"Amakiir (Gemflower)", "Amastacia (Starflower)", "Galanodel (Moonwhisper)", "Holimion (Diamonddew)", "Ilphelkiir (Gemblossom)",
			"Liadon (Silverfrond)", "Meliamne (Oakenheel)", "Nailo (Nightbreeze)", "Siannodel (Moonbrook)", "Xiloscient (Goldpetal)"
		}},

		{"Halfling", {
			"Brushgather", "Goodbarrel", "Greenbottle", "High-hill", "Hilltopple", "Leagallow", "Tealeaf", "Thorngage", "Tosscobble", "Underbough"
		}},

		{"Dragonborn", {
			"Clethtinihiallor", "Daardendrian", "Delmirev", "Drachedandion", "Fenkenkabradon", "Kepeshkmolik", "Kerrhylon", "Kimbatuul", "Linxakasendalor", 
			"Myastan", "Nemmonis", "Norixius", "Ophinshtalajiir", "Prexijandilin", "Shestendeliath", "Turnuroth", "Verthisathurgiesh", "Yarjerit"
		}},

		{"Gnome", {
			"Beren", "Daergel", "Folkor", "Garrick", "Nackle", "Murnig", "Ningel", "Raulnor", "Scheppen", "Timbers", "Turen"
		}},
	};

	const std::unordered_map<std::string, const std::vector<std::string>> NonHumanMaleNames = {
		{"Dwarf", {
			"Adrik", "Alberich", "Baern", "Barendd", "Brotto", "Bruenor", "Dain", "Darrak", "Delg", "Eberk",
			"Einkill", "Fargrim", "Flint", "Gardain", "Harbek", "Kildrak", "Morgran", "Orsik", "Oskar", "Rangrim",
			"Rurik", "Taklinn", "Thoradin", "Thorin", "Tordek", "Traubon", "Travok", "Ulfgar", "Veit", "Vondal"
		}},

		{"Elf", {
			"Adran", "Aelar", "Aramil", "Arannis", "Aust", "Beiro", "Berrian", "Carric", "Enialis", "Erdan",
			"Erevan", "Galinndan", "Hadarai", "Heian", "Himo", "Immeral", "Ivellios", "Laucian", "Mindartis", "Paelias",
			"Peren", "Quarion", "Riardon", "Rolen", "Soveliss", "Thamior", "Tharivol", "Theren", "Varis"
		}},

		{"Halfling", {
			"Alton", "Ander", "Cade", "Corrin", "Eldon", "Errich", "Finnan", "Farret", "Lindal", "Lyle",
			"Merric", "Milo", "Osborn", "Perrin", "Reed", "Roscoe", "Wellby"
		}},

		{"Dragonborn", {
			"Arjhan", "Balasar", "Bharash", "Donaar", "Ghesh", "Heskan", "Kriv", "Medrash", "Mehen", "Nadarr", "Pandjed", 
			"Patrin", "Rhogar", "Shamash", "Shedinn", "Tarhun", "Torinn"
		}},

		{"Gnome", {
			"Alston", "Alvyn", "Boddynock", "Brocc", "Burgell", "Dimble", "Eldon", "Erky", "Fonkin", "Frug", "Gerbo", "Gimble", 
			"Glim", "Jebeddo", "Kellen", "Namfoodle", "Orryn", "Roondar", "Seebo", "Sindri", "Warryn", "Wrenn", "Zook"
		}},

		{"Half-Orc", {
			"Dench", "Feng", "Gell", "Henk", "Holg", "Imsh", "Keth", "Krusk", "Mhurren", "Ront", "Shump", "Thokk"
		}},

		{"Tiefling", {
			"Akmenos", "Amnon", "Barakas", "Damakos", "Ekemon", "Iados", "Kairon", "Leucis", "Melech", "Mordai", "Morthos", "Pelaios", "Skamos", "Therai"
		}}
	};

	const std::unordered_map<std::string, const std::vector<std::string>> NonHumanFemaleNames = {
		{"Dwarf", {
			"Amber", "Artin", "Audhild", "Bardryn", "Dagnal", "Diesa", "Eldeth", "Falkrunn", "Finellen", "Gunnolda",
			"Gurdis", "Helja", "Hlin", "Kathra", "Kristryd", "Ilde", "Liftrasa", "Mandred", "Riswynn", "Sannl",
			"Torbera", "Torgga", "Vistra"
		}},

		{"Elf", {
			"Adrie", "Athaea", "Anastrianna", "Andraste", "Antinua", "Bethrynna", "Brel", "Caelynn", "Drusilia", "Enna",
			"Felosial", "Ielenia", "Jelenneth", "Keyleth", "Leshanna", "Lia", "Meriele", "Mialee", "Naivara", "Quelenna",
			"Quillathe", "Sariel", "Sanairra", "Shava", "Silaqui", "Theirastra", "Thia", "Vadania", "Valanthe", "Xanaphia"
		}},

		{"Halfling", {
			"Andry", "Bree", "Callie", "Cora", "Euphemia", "Jillian", "Kithri", "Lavania", "Lidda", "Meria",
			"Nedda", "Paela", "Portia", "Seraphina", "Shaena", "Trym", "Vani", "Verna"
		}},

		{"Dragonborn", {
			"Akra", "Biri", "Daar", "Farideh", "Harann", "Halivar", "Jheri", "Kava", "Korinn", "Mishann", "Nala", "Perra",
			"Raiann", "Sora", "Surina", "Thava", "Uadjit"
		}},

		{"Gnome", {
			"Bimpnottin", "Breena", "Caramip", "Carlin", "Donella", "Duvamil", "Ella", "Ellyjobell", "Ellywick", "Lilli",
			"Loopmottin", "Lorilla", "Mardnab", "Nissa", "Nyx", "Oda", "Orla", "Roywyn", "Shamil", "Tana", "Waywocket", "Zanna"
		}},

		{"Half-Orc", {
			"Baggi", "Emen", "Engong", "Kansif", "Myev", "Neega", "Ovak", "Ownka", "Shautha", "Sutha", "Vola", "Volen", "Yevelda"
		}},

		{"Tiefling", {
			"Akta", "Anakis", "Bryseis", "Criella", "Damaia", "Ea", "Kallista", "Lerissa", "Makaria", "Nemeia", "Orianna", "Phelaia", "Rieta"
		}}
	};

	const std::vector<std::string> VirtueNames = {
			"Art", "Carrion", "Chant", "Creed", "Despair", "Excellence", "Fear", "Glory", "Hope", "Ideal", "Music", "Nowhere", "Open", "Poetry", 
			"Quest", "Random", "Reverence", "Sorrow", "Temerity", "Torment", "Weary"
	};

	// ======================================================================================
	// Human Names
	// ======================================================================================

	const std::unordered_map<std::string, const std::vector<std::string>> HumanSurnames = {
		{"Calishite",  {"Basha", "Dumein", "Hassan", "Khalid", "Mostana", "Pashar", "Rein"}},
		{"Chondathan", {"Amblecrown", "Buckman", "Dundragon", "Evenwood", "Greycastle", "Tallstag"}},
		{"Tethyrian",  {"Amblecrown", "Buckman", "Dundragon", "Evenwood", "Greycastle", "Tallstag"}},
		{"Damaran",    {"Bersk", "Bernin", "Dotsk", "Kulenov", "Marsk", "Nemetsk", "Shemov", "Starag"}},
		{"Illuskan",   {"Brightwood", "Helder", "Hornraven", "Lackman", "Stormwind", "Windrivver"}},
		{"Mulan",      {"Ankhalah", "Anskuld", "Fezim", "Hahpet", "Nathandem", "Serpet", "Uuthrakt"}},
		{"Rashemi",    {"Chergoba", "Dyernina", "Iltazyara", "Murnyethara", "Stayanoga", "Ulmokina"}},
		{"Shou",       {"Chien", "Huang", "Kao", "Kung", "Lao", "Ling", "Mei", "Pin", "Shin", "Sum", "Tan", "Wan"}},
		{"Turami",     {"Agosto", "Astorio", "Calabra", "Domine", "Falone", "Marivaldi", "Pisacar", "Ramondo"}}
	};

	const std::unordered_map<std::string, const std::vector<std::string>> HumanMaleNames = {
		{"Calishite",  {"Aseir", "Bardeid", "Haseid", "Khemed", "Mehmen", "Sudeiman", "Zasheir"}},
		{"Chondathan", {"Darvin", "Dorn", "Evendur", "Gorstag", "Grim", "Helm", "Malark", "Morn", "Randal", "Stedd"}},
		{"Tethyrian",  {"Darvin", "Dorn", "Evendur", "Gorstag", "Grim", "Helm", "Malark", "Morn", "Randal", "Stedd"}},
		{"Damaran",    {"Bor", "Fodel", "Glar", "Grigor", "Igan", "Ivor", "Kosef", "Mival", "Orel", "Pavel", "Sergor"}},
		{"Illuskan",   {"Ander", "Blath", "Bran", "Frath", "Geth", "Lander", "Luth", "Malcer", "Stor", "Taman", "Urth"}},
		{"Mulan",      {"Aoth", "Bareris", "Ehput-Ki", "Kethoth", "Mumed", "Ramas", "So-Kehur", "Thazar-De", "Urhur"}},
		{"Rashemi",    {"Borivik", "Faurgar", "Jandar", "Kanithar", "Madislak", "Ralmevik", "Shaumar", "Vladislak"}},
		{"Shou",       {"An", "Chen", "Chi", "Fai", "Jiang", "Jun", "Lian", "Long", "Meng", "On", "Shan", "Shui", "Wen"}},
		{"Turami",     {"Anton", "Diero", "Marcon", "Pieron", "Rimardo", "Romero", "Salazar", "Umbero"}}
	};

	const std::unordered_map<std::string, const std::vector<std::string>> HumanFemaleNames = {
		{"Calishite",  {"Atala", "Ceidil", "Hama", "Jasmal", "Meilil", "Seipora", "Yasheria", "Zasheida"}},
		{"Chondathan", {"Arveene", "Esvele", "Jhessail", "Kerri", "Lureene", "Mirir", "Rowan", "Shandri", "Tessele"}},
		{"Tethyrian",  {"Arveene", "Esvele", "Jhessail", "Kerri", "Lureene", "Mirir", "Rowan", "Shandri", "Tessele"}},
		{"Damaran",    {"Alethra", "Kara", "Katernin", "Mara", "Natali", "Olma", "Tana", "Zora"}},
		{"Illuskan",   {"Amafrey", "Betha", "Cefrey", "Kethra", "Mara", "Olga", "Silifrey", "Westra"}},
		{"Mulan",      {"Arizima", "Chathi", "Nephis", "Nulara", "Murithi", "Sefris", "Thola", "Umara", "Zolis"}},
		{"Rashemi",    {"Fyevarra", "Hulmarra", "Immith", "Imzel", "Nevarra", "Shevarra", "Tammith", "Yuldra"}},
		{"Shou",       {"Bai", "Chao", "Jia", "Lei", "Mei", "Qiao", "Shui", "Tai"}},
		{"Turami",     {"Balama", "Dona", "Faila", "Jalana", "Luisa", "Marta", "Quara", "Selise", "Vonda"}}
	};

	// ======================================================================================
	// Personality Traits
	// ======================================================================================

	const std::unordered_map<std::string, std::vector<std::string>> PersonalityTraits = {
		{"Acolyte", {
			"I idolize a particular hero of my faith, and constantly refer to that person's deeds and example.",
			"I can find common ground between the fiercest enemies, empathizing with themand always working toward peace.",
			"I see omens in every eventand action. The gods try to speak to us, we just need to listen.",
			"Nothing can shake my optimistic attitude.",
			"I quote (or misquote) sacred textsand proverbs in almost every situation.",
			"I am tolerant (or intolerant) of other faithsand respect (or condemn) the worship of other gods.",
			"I've enjoyed fine food, drink, and high society among my temple's elite. Rough living grates on me.",
			"I've spent so long in the temple that I have little practical experience dealing with people in the outside world."
		}},

		{"Charlatan", {
			"I fall in and out of love easily, and am always pursuing someone.",
			"I have a joke for every occasion, especially occasions where humor is inappropriate.",
			"Flattery is my preferred trick for getting what I want.",
			"I'm a born gambler who can't resist taking a risk for a potential payoff.",
			"I lie about almost everything, even when there's no good reason to.",
			"Sarcasm and insults are my weapon of choice.",
			"I keep multiple holy symbols on me and invoke whatever deity might come in useful at any given moment.",
			"I pocket anything I see that might have some value."
		}},

		{"Criminal", {
			"I always have a plan for what to do when things go wrong.",
			"I am always calm, no matter what the situation.I never raise my voice or let my emotions control me.",
			"The first thing I do in a new place is note the locations of everything valuable--or where such things could be hidden.",
			"I would rather make a new friend than a new enemy.",
			"I am incredibly slow to trust. Those who seem the fairest often have the most to hide.",
			"I don't pay attention to the risks in a situation. Never tell me the odds.",
			"The best way to get me to do something is to tell me I can't do it.",
			"I blow up at the slightest insult."
		}},

		{"Spy", {
			"I always have a plan for what to do when things go wrong.",
			"I am always calm, no matter what the situation.I never raise my voice or let my emotions control me.",
			"The first thing I do in a new place is note the locations of everything valuable--or where such things could be hidden.",
			"I would rather make a new friend than a new enemy.",
			"I am incredibly slow to trust. Those who seem the fairest often have the most to hide.",
			"I don't pay attention to the risks in a situation. Never tell me the odds.",
			"The best way to get me to do something is to tell me I can't do it.",
			"I blow up at the slightest insult."
		}},

		{"Entertainer", {
			"I know a story relevant to almost every situation.",
			"Whenever I come to a new place, I collect local rumorsand spread gossip.",
			"I'm a hopeless romantic, always searching for that \"special someone.\"",
			"Nobody stays angry at me or around me for long, since I can defuse any amount of tension.",
			"I love a good insult, even one directed at me.",
			"I get bitter if I'm not the center of attention.",
			"I'll settle for nothing less than perfection.",
			"I change my mood or my mind as quickly as I change key in a song."
		}},

		{"Gladiator", {
			"I know a story relevant to almost every situation.",
			"Whenever I come to a new place, I collect local rumorsand spread gossip.",
			"I'm a hopeless romantic, always searching for that \"special someone.\"",
			"Nobody stays angry at me or around me for long, since I can defuse any amount of tension.",
			"I love a good insult, even one directed at me.",
			"I get bitter if I'm not the center of attention.",
			"I'll settle for nothing less than perfection.",
			"I change my mood or my mind as quickly as I change key in a song."
		}},

		{"Folk Hero", {
			"I judge people by their actions, not by their words.",
			"If someone is in trouble, I'm always ready to lend help.",
			"When I set my mind to do something, I follow through no matter what gets in my way.",
			"I have a strong sense of fair playand always try to find the most equitable solution to arguments.",
			"I'm confident in my own abilities and do what I can to instill confidence in others. ",
			"Thinking is for other people. I prefer action.",
			"I misuse long words in an attempt to sound smarter.",
			"I get bored easily. When am I going to get on with my destiny?"
		}},

		{"Guild Artisan", {
			"I believe that anything worth doing is worth doing right. I can't help it--I'm a perfectionist.",
			"I'm a snob who looks down on those who can't appreciate fine art.",
			"I always want to know how things work and what makes people tick.",
			"I'm full of witty aphorisms and have a proverb for every occasion.",
			"I'm rude to people who lack my own commitment to hard work and fair play.",
			"I like to talk at length about my profession.",
			"I don't part with my money easily and will haggle tirelessly to get the best deal possible.",
			"I'm well known for my work, and I want to make sure everyone appreciates it. I'm always taken aback when people haven't heard of me."
		}},

		{"Guild Merchant", {
			"I believe that anything worth doing is worth doing right. I can't help it--I'm a perfectionist.",
			"I'm a snob who looks down on those who can't appreciate fine art.",
			"I always want to know how things work and what makes people tick.",
			"I'm full of witty aphorisms and have a proverb for every occasion.",
			"I'm rude to people who lack my own commitment to hard work and fair play.",
			"I like to talk at length about my profession.",
			"I don't part with my money easily and will haggle tirelessly to get the best deal possible.",
			"I'm well known for my work, and I want to make sure everyone appreciates it. I'm always taken aback when people haven't heard of me."
		}},

		{"Hermit", {
			"I've been isolated for so long that I rarely speak, preferring gestures and the occasional grunt.",
			"I am utterly serene, even in the face of disaster.",
			"The leader of my community had something wise to say on every topic, and I am eager to share that wisdom.",
			"I feel tremendous empathy for all who suffer.",
			"I'm oblivious to etiquette and social expectations.",
			"I connect everything that happens to me to a grand, cosmic plan.",
			"I often get lost in my own thoughtsand contemplation, becoming oblivious to my surroundings.",
			"I am working on a grand philosophical theory and love sharing my ideas."
		}},

		{"Noble", {
			"My eloquent flattery makes everyone I talk to feel like the most wonderful and important person in the world.",
			"The common folk love me for my kindness and generosity.",
			"No one could doubt by looking at my regal bearing that I am a cut above the unwashed masses.",
			"I take great pains to always look my bestand follow the latest fashions.",
			"I don't like to get my hands dirty, and I won't be caught dead in unsuitable accommodations.",
			"Despite my noble birth, I do not place myself above other folk.We all have the same blood.",
			"My favor, once lost, is lost forever.",
			"If you do me an injury, I will crush you, ruin your name,and salt your fields."
		}},

		{"Knight", {
			"My eloquent flattery makes everyone I talk to feel like the most wonderful and important person in the world.",
			"The common folk love me for my kindness and generosity.",
			"No one could doubt by looking at my regal bearing that I am a cut above the unwashed masses.",
			"I take great pains to always look my bestand follow the latest fashions.",
			"I don't like to get my hands dirty, and I won't be caught dead in unsuitable accommodations.",
			"Despite my noble birth, I do not place myself above other folk.We all have the same blood.",
			"My favor, once lost, is lost forever.",
			"If you do me an injury, I will crush you, ruin your name,and salt your fields."
		}},

		{"Outlander", {
			"I'm driven by a wanderlust that led me away from home.",
			"I watch over my friends as if they were a litter of newborn pups.",
			"I once ran twenty-five miles without stopping to warn to my clan of an approaching orc horde. I'd do it again if I had to.",
			"I have a lesson for every situation, drawn from observing nature.",
			"I place no stock in wealthy or well-mannered folk. Money and manners won't save you from a hungry owlbear.",
			"I'm always picking things up, absently fiddling with them, and sometimes accidentally breaking them.",
			"I feel far more comfortable around animals than people.",
			"I was, in fact, raised by wolves."
		}},

		{"Sage", {
			"I use polysyllabic words that convey the impression of great erudition.",
			"I've read every book in the world's greatest libraries--or I like to boast that I have.",
			"I'm used to helping out those who aren't as smart as I am, and I patiently explain anythingand everything to others.",
			"There's nothing I like more than a good mystery.",
			"I'm willing to listen to every side of an argument before I make my own judgement.",
			"I . . . speak . . . slowly . . . when talking . . . to idiots, . . . which . . . almost . . . everyone . . . is . . . compared . . . to me.",
			"I am horribly, horribly awkward in social situations.",
			"I'm convinced that people are always trying to steal my secrets."
		}},

		{"Sailor", {
			"My friends know they can rely on me, no matter what.",
			"I work hard so that I can play hard when the work is done.",
			"I enjoy sailing into new portsand making new friends over a flagon of ale.",
			"I stretch the truth for the sake of a good story.",
			"To me, a tavern brawl is a nice way to get to know a new city.",
			"I never pass up a friendly wager.",
			"My language is as foul as an olyugh nest.",
			"I like a job well done, especially if I can convince someone else to do it."
		}},

		{"Pirate", {
			"My friends know they can rely on me, no matter what.",
			"I work hard so that I can play hard when the work is done.",
			"I enjoy sailing into new portsand making new friends over a flagon of ale.",
			"I stretch the truth for the sake of a good story.",
			"To me, a tavern brawl is a nice way to get to know a new city.",
			"I never pass up a friendly wager.",
			"My language is as foul as an olyugh nest.",
			"I like a job well done, especially if I can convince someone else to do it."
		}},

		{"Soldier", {
			"I'm always polite and respectful.",
			"I'm haunted by memories of war. I can't get the images of violence out of my mind.",
			"I've lost too many friends, and I'm slow to make new ones.",
			"I'm full of inspiring and cautionary tales from my military experience relevant to almost every combat situation.",
			"I can stare down a hell hound without flinching.",
			"I enjoy being strong and like breaking things.",
			"I have a crude sense of humor.",
			"I face problems head-on. A simple, direct solution is the best path so success."
		}},

		{"Urchin", {
			"I hide scraps of food and trinkets away in my pockets.",
			"I ask a lot of questions.",
			"I like to squeeze into small places where no one else can get to me.",
			"I sleep with my back to a wall or tree, with everything I own wrapped in a bundle in my arms.",
			"I eat like a pigand have bad manners.",
			"I think anyone who's nice to me is hiding evil intent.",
			"I don't like to bathe.",
			"I bluntly say what other people are hinting at or hiding."
		}}
	};

	// ======================================================================================
	// Ideals
	// ======================================================================================

	const std::unordered_map<std::string, const std::vector<std::pair<std::string, std::string>>> Ideals = {
		{"Acolyte", {
			{"Lawful",  "Tradition. The ancient traditions of worship and sacrifice must be preserved and upheld."},
			{"Good",    "Charity. I always try to help those in need, no matter what the personal cost."},
			{"Chaotic", "Change. We must help bring about the changes the gods are constantly working in the world."},
			{"Lawful",  "Power. I hope to one day rise to the top of my faith's religious hierarchy."},
			{"Lawful",  "Faith. I trust that my deity will guide my actions.I have faith that if I work hard, things will go well."},
			{"Any",     "Aspiration. I seek to prove myself worthy of my god's favor by matching my actions against his or her teachings."}
		}},

		{"Charlatan", {
			{"Lawful",  "Tradition. The ancient traditions of worship and sacrifice must be preserved and upheld."},
			{"Good",    "Charity. I always try to help those in need, no matter what the personal cost."},
			{"Chaotic", "Change. We must help bring about the changes the gods are constantly working in the world."},
			{"Lawful",  "Power. I hope to one day rise to the top of my faith's religious hierarchy."},
			{"Lawful",  "Faith. I trust that my deity will guide my actions.I have faith that if I work hard, things will go well."},
			{"Any",     "Aspiration. I seek to prove myself worthy of my god's favor by matching my actions against his or her teachings."}
		}},

		{"Criminal", {
			{"Lawful",  "Honor. I don't steal from others in the trade."},
			{"Chaotic", "Freedom. Chains are meant to be broken, as are those who would forge them."},
			{"Good",    "Charity. I steal from the wealthy so that I can help people in need."},
			{"Evil",    "Greed. I will do whatever it takes to become wealthy."},
			{"Neutral", "People. I'm loyal to my friends, not to any ideals, and everyone else can take a trip down the Styx for all I care."},
			{"Good",    "Redemption. There's a spark of good in everyone."}
		}},

		{"Spy", {
			{"Lawful",  "Honor. I don't steal from others in the trade."},
			{"Chaotic", "Freedom. Chains are meant to be broken, as are those who would forge them."},
			{"Good",    "Charity. I steal from the wealthy so that I can help people in need."},
			{"Evil",    "Greed. I will do whatever it takes to become wealthy."},
			{"Neutral", "People. I'm loyal to my friends, not to any ideals, and everyone else can take a trip down the Styx for all I care."},
			{"Good",    "Redemption. There's a spark of good in everyone."}
		}},

		{"Entertainer", {
			{"Good",    "Beauty. When I perform, I make the world better than it was."},
			{"Lawful",  "Tradition. The stories, legends, and songs of the past must never be forgotten, for they teach us who we are."},
			{"Chaotic", "Creativity. The world is in need of new ideas and bold action."},
			{"Evil",    "Greed. I'm only in it for the money and fame."},
			{"Neutral", "People. I like seeing the smiles on people's faces when I perform. That's all that matters."},
			{"Any",     "Honesty. Art should reflect the soul; it should come from within and reveal who we really are."}
		}},

		{"Gladiator", {
			{"Good",    "Beauty. When I perform, I make the world better than it was."},
			{"Lawful",  "Tradition. The stories, legends, and songs of the past must never be forgotten, for they teach us who we are."},
			{"Chaotic", "Creativity. The world is in need of new ideas and bold action."},
			{"Evil",    "Greed. I'm only in it for the money and fame."},
			{"Neutral", "People. I like seeing the smiles on people's faces when I perform. That's all that matters."},
			{"Any",     "Honesty. Art should reflect the soul; it should come from within and reveal who we really are."}
		}},

		{"Folk Hero", {
			{"Good",    "Respect. People deserve to be treated with dignity and respect."},
			{"Lawful",  "Fairness. No one should get preferential treatment before the law,and no one is above the law."},
			{"Chaotic", "Freedom. Tyrants must not be allowed to oppress the people."},
			{"Evil",    "Might. If I become strong, I can take what I want--what I deserve."},
			{"Neutral", "Sincerity. There's no good in pretending to be something I'm not."},
			{"Any",     "Destiny. Nothing and no one can steer me away from my higher calling."}
		}},

		{"Guild Artisan", {
			{"Lawful",  "Community. It is the duty of all civilized people to strengthen the bonds of community and the security of civilization."},
			{"Good",    "Generosity. My talents were given to me so that I could use them to benefit the world."},
			{"Chaotic", "Freedom. Everyone should be free to pursue his or her own livelihood."},
			{"Evil",    "Greed. I'm only in it for the money."},
			{"Neutral", "People. I'm committed to the people I care about, not to ideals."},
			{"Any",     "Aspiration. I work hard to be the best there is at my craft."}
		}},

		{"Guild Merchant", {
			{"Lawful",  "Community. It is the duty of all civilized people to strengthen the bonds of community and the security of civilization."},
			{"Good",    "Generosity. My talents were given to me so that I could use them to benefit the world."},
			{"Chaotic", "Freedom. Everyone should be free to pursue his or her own livelihood."},
			{"Evil",    "Greed. I'm only in it for the money."},
			{"Neutral", "People. I'm committed to the people I care about, not to ideals."},
			{"Any",     "Aspiration. I work hard to be the best there is at my craft."}
		}},

		{"Hermit", {
			{"Good",    "Greater Good. My gifts are meant to be shared with all, not used for my own benefit."},
			{"Lawful",  "Logic. Emotions must not cloud our sense of what is right and true, or our logical thinking"},
			{"Chaotic", "Free Thinking. Inquiry and curiosity are the pillars of progress."},
			{"Evil",    "Power. Solitude and contemplation are paths toward mystical or magical power."},
			{"Neutral", "Live and Let Live. Meddling in the affairs of others only causes trouble."},
			{"Any",     "Self-Knowledge. If you know yourself, there's nothing left to know."}
		}},

		{"Noble", {
			{"Good",    "Respect. Respect is due to me because of my position, but all people regardless of station deserve to be treated with dignity."},
			{"Lawful",  "Responsibility. It is my duty to respect the authority of those above me, just as those below me must respect mine."},
			{"Chaotic", "Independence. I must prove that I can handle myself without the coddling of my family."},
			{"Evil",    "Power. If I can attain more power, no one will tell me what to do."},
			{"Any",     "Family. Blood runs thicker than water."},
			{"Good",    "Noble Obligation. It is my duty to protect and care for the people beneath me."}
		}},

		{"Knight", {
			{"Good",    "Respect. Respect is due to me because of my position, but all people regardless of station deserve to be treated with dignity."},
			{"Lawful",  "Responsibility. It is my duty to respect the authority of those above me, just as those below me must respect mine."},
			{"Chaotic", "Independence. I must prove that I can handle myself without the coddling of my family."},
			{"Evil",    "Power. If I can attain more power, no one will tell me what to do."},
			{"Any",     "Family. Blood runs thicker than water."},
			{"Good",    "Noble Obligation. It is my duty to protect and care for the people beneath me."}
		}},

		{"Outlander", {
			{"Chaotic", "Change. Life is like the seasons, in constant change, and we must change with it."},
			{"Good",    "Greater Good. It is each person's responsibility to make the most happiness for the whole tribe."},
			{"Lawful",  "Honor. If I dishonor myself, I dishonor my whole clan."},
			{"Evil",    "Might. The strongest are meant to rule."},
			{"Neutral", "Nature. The natural world is more important than all the constructs of civilization."},
			{"Any",     "Glory. I must earn glory in battle, for myself and my clan."}
		}},

		{"Sage", {
			{"Neutral", "Knowledge. The path to power and self-improvement is through knowledge."},
			{"Good",    "Beauty. What is beautiful points us beyond itself toward what is true."},
			{"Lawful",  "Logic. Emotions must not cloud our logical thinking."},
			{"Chaotic", "No Limits. Nothing should fetter the infinite possibility inherent in all existence."},
			{"Evil",    "Power. Knowledge is the path to power and domination."},
			{"Any",     "Self-Improvement. The goal of a life to study is the betterment of oneself."}
		}},

		{"Sailor", {
			{"Good",    "Respect. The thing that keeps a ship together is mutual respect between captain and crew."},
			{"Lawful",  "Fairness. We all do the work, so we all share in the rewards"},
			{"Chaotic", "Freedom. The sea is freedom--the freedom to go anywhere and do anything."},
			{"Evil",    "Mastery. I'm a predator, and the other ships on the sea are my prey."},
			{"Neutral", "People. I'm committed to my crewmates, not to ideals."},
			{"Any",     "Aspiration. Someday I'll own my own ship and chart my own destiny."}
		}},

		{"Pirate", {
			{"Good",    "Respect. The thing that keeps a ship together is mutual respect between captain and crew."},
			{"Lawful",  "Fairness. We all do the work, so we all share in the rewards"},
			{"Chaotic", "Freedom. The sea is freedom--the freedom to go anywhere and do anything."},
			{"Evil",    "Mastery. I'm a predator, and the other ships on the sea are my prey."},
			{"Neutral", "People. I'm committed to my crewmates, not to ideals."},
			{"Any",     "Aspiration. Someday I'll own my own ship and chart my own destiny."}
		}},

		{"Soldier", {
			{"Good",    "Greater Good. Our lot is to lay down our lives in defense of others."},
			{"Lawful",  "Responsibility. I do what I mustand obey just authority."},
			{"Chaotic", "Independnce. When people follow order blindly, they embrace a kind of tyranny."},
			{"Evil",    "Might. In life as in war, the stronger force wins."},
			{"Neutral", "Live and Let Live. Ideals aren't worth killing over or going to war for."},
			{"Any",     "Nation. My city, nation, or people are all that matter."}
		}},

		{"Urchin", {
			{"Good",    "Repsect. All people, rich or poor, deserve respect."},
			{"Lawful",  "Community. We have to take care of each other, because no one else is going to do it."},
			{"Chaotic", "Change. The low are lifted up,and the highand mighty are brought down. Change is the nature of things."},
			{"Evil",    "Retribution. The rich need to be shown what life and death are like in the gutters."},
			{"Neutral", "People. I help the people who help me--that's what keeps us alive."},
			{"Any",     "Aspiration. I'm going to prove that I'm worthy of a better life."}
		}}
	};

	// ======================================================================================
	// Bonds
	// ======================================================================================

	const std::unordered_map<std::string, const std::vector<std::string>> Bonds = {
		{"Acolyte", {
			"I would die to recover an ancient relic of my faith that was lost long ago.",
			"I will someday get revenge on the corrupt temple hierarchy who branded me a heretic.",
			"I owe my life to the priest who took me in when my parents died.",
			"Everything I do is for the common people.",
			"I will do anything to protect the temple where I served.",
			"I seek to preserve a sacred text that my enemies consider heretical and seek to destroy."
		}},

		{"Charlatan", {
			"I fleeced the wrong personand must work to ensure that this individual never crosses paths with me or those I care about.",
			"I owe everything to my mentor--a horrible person who's probably rotting in jail somewhere.",
			"Somewhere out there, I have a child who doesn't know me. I'm making the world better for him or her.",
			"I come from a noble family, and one day I'll reclaim my lands and title from those who stole them from me.",
			"A powerful person killed someone I love. Some day soon, I'll have my revenge.",
			"I swindled and ruined a person who didn't deserve it. I seek to atone for my misdeeds but might never be able to forgive myself."
		}},

		{"Criminal", {
			"I'm trying to pay off an old debt I owe to a generous benefactor.",
			"My ill-gotten gains go to support my family.",
			"Something important was taken from me, and I aim to steal it back.",
			"I will become the greatest thief that ever lived.",
			"I'm guilty of a terrible crime. I hope I can redeem myself for it.",
			"Someone I loved died because of a mistake I made. That will never happen again."
		}},

		{"Spy", {
			"I'm trying to pay off an old debt I owe to a generous benefactor.",
			"My ill-gotten gains go to support my family.",
			"Something important was taken from me, and I aim to steal it back.",
			"I will become the greatest thief that ever lived.",
			"I'm guilty of a terrible crime. I hope I can redeem myself for it.",
			"Someone I loved died because of a mistake I made. That will never happen again."
		}},

		{"Entertainer", {
			"My instrument is my most treasured possession, and it reminds me of someone I love.",
			"Someone stole my precious instrument, and someday I'll get it back.",
			"I want to be famous, whatever it takes.",
			"I idolize a hero of the old talesand measure my deeds against that person's.",
			"I will do anything to prove myself superior to my hated rival.",
			"I would do anything for the old members of my old troupe."
		}},

		{"Gladiator", {
			"My instrument is my most treasured possession, and it reminds me of someone I love.",
			"Someone stole my precious instrument, and someday I'll get it back.",
			"I want to be famous, whatever it takes.",
			"I idolize a hero of the old talesand measure my deeds against that person's.",
			"I will do anything to prove myself superior to my hated rival.",
			"I would do anything for the old members of my old troupe."
		}},

		{"Folk Hero", {
			"I have a family, but I have no idea where they are. One day, I hope to see them again.",
			"I worked the land, I love the land, and I will protect the land.",
			"A proud noble once gave me a horrible beating, and I will take my revenge on any bully I encounter.",
			"My tools are symbols of my past life, and I carry them so that I will never forget my roots.",
			"I protect those who cannot protect themselves.",
			"I wish my childhood sweetheart had come with me to pursue my destiny."
		}},

		{"Guild Artisan", {
			"The workshop where I learned my trade is the most important place in the world to me.",
			"I created a great work for someone, and then found them unworthy to receive it. I'm still looking for someone worthy.",
			"I owe my guild a great debt for forging me into the person I am today.",
			"I pursue wealth to secure someone's love.",
			"One day I will return to my guild and prove that I am the greatest artisan of them all.",
			"I will get revenge on the evil forces that destroyed my place of business and ruined my livelihood."
		}},

		{"Guild Merchant", {
			"The workshop where I learned my trade is the most important place in the world to me.",
			"I created a great work for someone, and then found them unworthy to receive it. I'm still looking for someone worthy.",
			"I owe my guild a great debt for forging me into the person I am today.",
			"I pursue wealth to secure someone's love.",
			"One day I will return to my guild and prove that I am the greatest artisan of them all.",
			"I will get revenge on the evil forces that destroyed my place of business and ruined my livelihood."
		}},

		{"Hermit", {
			"Nothing is more important than the other members of my hermitage, order, or association.",
			"I entered seclusion to hide from the ones who might still be hunting me. I must someday confront them.",
			"I'm still seeking the enlightenment I pursued in my seclusion, and it still eludes me.",
			"I entered seclusion because I loved someone I could not have.",
			"Should my discovery come to light, it could bring ruin to the world.",
			"My isolation gave me great insight into a great evil that only I can destroy."
		}},

		{"Noble", {
			"I will face any challenge to win the approval of my family.",
			"My house's alliance with another noble family must be sustained at all costs.",
			"Nothing is more important than the other members of my family.",
			"I am in love with the heir of a family that my family despises.",
			"My loyalty to my sovereign is unwavering.",
			"The common folk must see me as a hero of the people."
		}},

		{"Knight", {
			"I will face any challenge to win the approval of my family.",
			"My house's alliance with another noble family must be sustained at all costs.",
			"Nothing is more important than the other members of my family.",
			"I am in love with the heir of a family that my family despises.",
			"My loyalty to my sovereign is unwavering.",
			"The common folk must see me as a hero of the people."
		}},

		{"Outlander", {
			"My family, clan, or tribe is the most important thing in my life, even when they are far from me.",
			"An injury to the unspoiled wilderness of my home is an injury to me.",
			"I will bring terrible wrath down on the evildoers who destroyed my homeland.",
			"I am the last of my tribe, and it is up to me to ensure their names enter legend.",
			"I suffer awful visions of a coming disasterand will do anything to prevent it.",
			"It is my duty to provide children to sustain my tribe."
		}},

		{"Sage", {
			"It is my duty to protect my students.",
			"I have an ancient text that holds terrible secrets that must not fall into the wrong hands.",
			"I work to preserve a library, university, scriptorium, or monastery.",
			"My life's work is a series of tomes related to a specific field of lore.",
			"I've been searching my whole life for the answer to a certain question.",
			"I sold my soul for knowledge. I hope to do great deeds and win it back."
		}},

		{"Sailor", {
			"I'm loyal to my captain first, everything else second.",
			"The ship is most important--crewmates and captains come and go.",
			"I'll always remember my first ship.",
			"In a harbor town, I have a paramour whose eyes nearly stole me from the sea.",
			"I was cheated out of my fair share of the profits, and I want to get my due.",
			"Ruthless pirates murdered my captain and crewmates, plundered our ship, and left me to die. Vengeance will be mine."
		}},

		{"Pirate", {
			"I'm loyal to my captain first, everything else second.",
			"The ship is most important--crewmates and captains come and go.",
			"I'll always remember my first ship.",
			"In a harbor town, I have a paramour whose eyes nearly stole me from the sea.",
			"I was cheated out of my fair share of the profits, and I want to get my due.",
			"Ruthless pirates murdered my captain and crewmates, plundered our ship, and left me to die. Vengeance will be mine."
		}},

		{"Soldier", {
			"I would still lay down my life for the people I served with.",
			"Someone saved my life on the battlefield. To this day, I will never leave a friend behind.",
			"My honor is my life.",
			"I'll never forget the crushing defeat my company suffered or the enemies who dealt it.",
			"Those who fight beside me are those worth dying for.",
			"I fight for those who cannot fight for themselves."
		}},

		{"Urchin", {
			"My town or city is my home,and I'll fight to defend it.",
			"I sponsor an orphanage to keep others from enduring what I was forced to endure.",
			"I owe my survival to another urchin who taught me to live on the streets.",
			"I owe a debt I can never repay to the person who took pity on me.",
			"I escaped my life poverty by robbing an important person, and I'm wanted for it.",
			"No one else should have to endure the hardships I've been through."
		}}
	};

	// ======================================================================================
	// Flaws
	// ======================================================================================

	const std::unordered_map<std::string, const std::vector<std::string>> Flaws = {
		{"Acolyte", {
			"I judge others harshly, and myself even more severely.",
			"I put too much trust in those who wield power within my temple's hierarchy.",
			"My piety sometimes leads me to blindly trust those that profess faith in my god.",
			"I am inflexible in my thinking.",
			"I am suspicious of strangers and expect the worst of them.",
			"Once I pick a goal, I become obsessed with it to the detriment of everything else in my life."
		}},

		{"Charlatan", {
			"I can't resist a pretty face.",
			"I'm always in debt. I spend my ill-gotten gains on decadent luxuries faster than I bring them in.",
			"I'm convinced that no one could ever fool me the way I fool others.",
			"I'm too greedy for my own good. I can't resist taking a risk if there's money involved.",
			"I can't resist swindling people who are more powerful than me.",
			"I hate to admit it and will hate myself for it, but I'll run and preserve my own hide if the going gets tough."
		}},

		{"Criminal", {
			"When I see something valuable, I can't think about anything but how to steal it.",
			"When faced with a choice between money and my friends, I usually choose the money.",
			"If there's a plan, I'll forget it.If I don't forget it, I'll ignore it.",
			"I have a \"tell\" that reveals when I'm lying.",
			"I turn tail and run when things look bad.",
			"An innocent person is in prison for a crime that I committed. I'm okay with that."
		}},

		{"Spy", {
			"When I see something valuable, I can't think about anything but how to steal it.",
			"When faced with a choice between money and my friends, I usually choose the money.",
			"If there's a plan, I'll forget it.If I don't forget it, I'll ignore it.",
			"I have a \"tell\" that reveals when I'm lying.",
			"I turn tail and run when things look bad.",
			"An innocent person is in prison for a crime that I committed. I'm okay with that."
		}},

		{"Entertainer", {
			"I'll do anything to win fame and renown.",
			"I'm a sucker for a pretty face.",
			"A scandal prevents me from ever going home again. That kind of trouble seems to follow me around.",
			"I once satirized a noble who still wants my head. It was a mistake that I will likely repeat.",
			"I have trouble keeping my true feeling hidden. My sharp tongue lands me in trouble.",
			"Despite my best efforts, I am unreliable to my friends."
		}},

		{"Gladiator", {
			"I'll do anything to win fame and renown.",
			"I'm a sucker for a pretty face.",
			"A scandal prevents me from ever going home again. That kind of trouble seems to follow me around.",
			"I once satirized a noble who still wants my head. It was a mistake that I will likely repeat.",
			"I have trouble keeping my true feeling hidden. My sharp tongue lands me in trouble.",
			"Despite my best efforts, I am unreliable to my friends."
		}},

		{"Folk Hero", {
			"The tyrant who rules my land will stop at nothing see me killed.",
			"I'm convinced of the significance of my destiny, and blind to my shortcomings and the risk of failure.",
			"The people who knew me when I was young know my shameful secret, so I can never go home again.",
			"I have a weakness for the vices of the city, especially hard drink.",
			"Secretly, I believe that things would be better if I were a tyrant lording over the land."
			"I have trouble trusting in my allies."
		}},

		{"Guild Artisan", {
			"I'll do anything to get my hands on something rare or priceless.",
			"I'm quick to assume that someone is trying to cheat me.",
			"No one must ever learn that I once stole money from guild coffers.",
			"I'm never satisfied with what I have--I always want more.",
			"I would kill to acquire a noble title.",
			"I'm horribly jealous of anyone who can outshine my handiwork. Everywhere I go, I'm surrounded by rivals."
		}},

		{"Guild Merchant", {
			"I'll do anything to get my hands on something rare or priceless.",
			"I'm quick to assume that someone is trying to cheat me.",
			"No one must ever learn that I once stole money from guild coffers.",
			"I'm never satisfied with what I have--I always want more.",
			"I would kill to acquire a noble title.",
			"I'm horribly jealous of anyone who can outshine my handiwork. Everywhere I go, I'm surrounded by rivals."
		}},

		{"Hermit", {
			"Now that I've returned to the world, I enjoy its delights a little too much.",
			"I harbor dark, bloodthirsty thoughts that my isolationand meditation failed to quell.",
			"I am dogmatic in my thoughtsand philosophy.",
			"I let my need to win arguments overshadow friendshipsand harmony.",
			"I'd risk too much to uncover a lost bit of knowledge.",
			"I like keeping secrets and won't share them with anyone."
		}},

		{"Noble", {
			"I secretly believe that everyone is beneath me.",
			"I hide a truly scandalous secret that could ruin my family forever.",
			"I too often hear veiled insults and threats in every word addressed to me, and I'm quick to anger.",
			"I have an insatiable desire for carnal pleasures.",
			"In fact, the world does revolve around me.",
			"By my wordsand actions, I often bring shame to my family."
		}},

		{"Knight", {
			"I secretly believe that everyone is beneath me.",
			"I hide a truly scandalous secret that could ruin my family forever.",
			"I too often hear veiled insults and threats in every word addressed to me, and I'm quick to anger.",
			"I have an insatiable desire for carnal pleasures.",
			"In fact, the world does revolve around me.",
			"By my wordsand actions, I often bring shame to my family."
		}},

		{"Outlander", {
			"I am too enamored of ale, wine, and other intoxicants.",
			"There's no room for caution in a life lived to the fullest.",
			"I remember every insult I've received and nurse a silent resentment toward anyone who's ever wronged me.",
			"I am slow to trust members of other races, tribes,and societies.",
			"Violence is my answer to almost any challenge.",
			"Don't expect me to save those who can't save themselves. It's nature's way that the strong thrive and the weak perish."
		}},

		{"Sage", {
			"I am easily distracted by the promise of information.",
			"Most people screamand run when they see a demon. I stopand take notes on its anatomy.",
			"Unlocking an ancient mystery is worth the price of a civilization.",
			"I overlook obvious solutions in favor of complicated ones.",
			"I speak without really thinking through my words, invariably insulting others.",
			"I can't keep a secret to save my life, or anyone else's."
		}},

		{"Sailor", {
			"I follow orders, even if I think they're wrong.",
			"I'll say anything to avoid having to do extra work.",
			"Once someone questions my courage, I never back down no matter how dangerous the situation.",
			"Once I start drinking, it's hard for me to stop.",
			"I can't help but pocket loose coins and other trinkets I come across.",
			"My pride will probably lead to my destruction."
		}},

		{"Pirate", {
			"I follow orders, even if I think they're wrong.",
			"I'll say anything to avoid having to do extra work.",
			"Once someone questions my courage, I never back down no matter how dangerous the situation.",
			"Once I start drinking, it's hard for me to stop.",
			"I can't help but pocket loose coins and other trinkets I come across.",
			"My pride will probably lead to my destruction."
		}},

		{"Soldier", {
			"The monstrous enemy we faced in battle still leaves me quivering with fear.",
			"I have little respect for anyone who is not a proven warrior.",
			"I made a terrible mistake in battle costing many lives--and I would do anything to keep that mistake secret.",
			"My hatred of my enemies is blindand unreasoning.",
			"I obey the law, even if the law causes misery.",
			"I'd rather eat my armor than admit I'm wrong."
		}},

		{"Urchin", {
			"If I'm outnumbered, I will run away from a fight.",
			"Gold seems like a lot of money to me, and I'll do just about anything for more of it.",
			"I will never fully trust anyone other than myself.",
			"I'd rather kill someone in their sleep than fight fair.",
			"It's not stealing if I need it more than someone else.",
			"People who can't take care of themselves get what they deserve."
		}}
	};

	// ======================================================================================
	// Features, Traits, and Proficiencies
	// ======================================================================================

	// Note: Starting a newline in the Trait constructor signifies a new paragraph.

	const std::unordered_map<std::string, const std::vector<Trait>> RacialFeats = {
		{"Dwarf", {
			Trait("Darkvision.", "Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray."),
			Trait("Dwarven Resilience.", "You have advantage on saving throws against poison, and you have resistance against poison damage."),
			Trait("Stonecunning.", "Whenever you make an Intelligence (History) check related to the origin of stonework, you are considered proficient in the History skill and add double your proficiency bonus to the check, instead of your normal proficiency bonus.")
		}},

		{"Hill Dwarf", {
			Trait("Dwarven Toughness.", "Your hit point maximum increases by 1, and it increases by 1 every time you gain a level.")
		}},

		{"Elf", {
			Trait("Darkvision.", "Accustomed to twilit forests and the night sky, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray."),
			Trait("Fey Ancestry.", "You have advantage on saving throws against being charmed, and magic can't put you to sleep."),
			Trait("Trance.", "Elves don't need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is \"Trance.\") While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep.")
		}},

		{"High Elf", {
			Trait("Cantrip.", "You know one cantrip of your choice from the wizard spell list. Intelligence is your spellcasting ability for it.")
		}},

		{"Wood Elf", {
			Trait("Mask of the Wild.", "You can attempt to hide even when you are only lightly obscured by foliage, heavy rain, falling snow, mist, and other natural phenomena.")
		}},

		{"Dark Elf (Drow)", {
			Trait("Superior Darkvision.", "Your darkvision has a radius of 120 feet."),
			Trait("Sunlight Sensitivity.", "You have disadvantage on attack rolls and on Wisdom (Perception) checks that rely on sight when you, the target of your attack, or whatever you are trying to perceive is in direct sunlight."),
			Trait("Drow Magic.", "You know the dancing lights cantrip. When you reach 3rd level, you can cast the faerie fire spell once per day. When you reach 5th level, you can also cast the darkness spell once per day. Charisma is your spellcasting ability for these spells.")
		}},

		{"Halfling", {
			Trait("Lucky.", "When you roll a 1 on an attack roll, ability check, or saving throw, you can reroll the die and must use the new roll."),
			Trait("Brave.", "You have advantage on saving throws against being frightened."),
			Trait("Halfling Nimbleness.", "You can move through the space of any creature that is of a size larger than you.")
		}},

		{"Lightfoot Halfling", {
			Trait("Naturally Stealthy.", "You can attempt to hide even when you are obscured only by a creature that is at least one size larger than you.")
		}},

		{"Stout Halfling", {
			Trait("Stout Resilience.", "You have advantage on saving throws against poison, and you have resistance against poison damage.")
		}},

		{"Dragonborn", {
			Trait("Draconic Ancestry.", "You have draconic ancestry. Choose one type of dragon from the Draconic Ancestry table in the rulebook. Your breath weapon and damage resistance are determined by the dragon type, as shown in the table."),
			Trait("Breath Weapon.", "You can use your action to exhale destructive energy. Your draconic ancestry determines the size, shape, and damage type of the exhalation.\n"
			                        "When you use your breath weapon, each creature in the area of the exhalation must take a saving throw, the type of which is determined by your draconic ancestry. The DC for this saving throw equals 8 + your Constitution modifier + your proficiency bonus. A creature takes 2d6 damage on a failed save, and half as much damage on a successful one. The damage increases to 3d6 at 6th level, 4d6 at 11th level, and 5d6 at 16th level.\n"
			                        "After you use your breath weapon, you can't use it again until you complete a short rest or a long rest."),
			Trait("Damage Resistance.", "You have resistance to the damage type associated with your draconic ancestry.")
		}},

		{"Gnome", {
			Trait("Darkvision.", "Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and and in darkness as if it were dim light. You can't discern color in the darkness, only shades of gray."),
			Trait("Gnome Cunning.", "You have advantage on all Intelligence, Wisdom, and Charisma saving throws against magic.")
		}},

		{"Forest Gnome", {
			Trait("Natural Illusionist.", "You know the minor illusion cantrip. Intelligence is your spellcasting ability for it."),
			Trait("Speak with Small Beasts.", "Through sounds and gestures, you can communicate simple ideas with Small or smaller beasts. Forest gnomes love animals and often keep squirells, badgers, rabbits, moles, woodpeckers, and other creatures as beloved pets")
		}},

		{"Rock Gnome", {
			Trait("Artificer's Lore.", "Whenever you make an Intelligence (History) check related to magic items, alchemical objects, or technological devices, you can add twice your proficiency bonus, instead of any proficiency bonus you normally apply"),
			Trait("Tinker.", "You have proficiency with artisan's tools (tinker's tools). Using those tools, you can spend 1 hour and 10 gp worth of materials to construct a Tiny clockwork device (AC 5, 1 hp). The device ceases to function after 24 hours (unless you spend 1 hour repairing it to keep the device functioning), or when you use your action to dismantle it; at that time, you can reclaim the materials used to create it. You can have up to three such devices active at a time.\n"
			                 "When you create a device, choose a Clockwork Toy, a Fire Starter, or a Music Box. Descriptions of these devices are found in the rulebook.")
		}},

		{"Half-Elf", {
			Trait("Darkvision.", "Thanks to your elf blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in the darkness, only shades of gray."),
			Trait("Fey Ancestry.", "You have advantage on saving throws against being charmed, and magic can't put you to sleep."),
			Trait("Skill Versatiility.", "You gain proficiency in two skills of your choice.")
		}},

		{"Half-Orc", {
			Trait("Darkvision.", "Thanks to your orc blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in the darkness, only shades of gray."),
			Trait("Menacing.", "You gain proficiency in the Intimidation skill."),
			Trait("Relentless Endurance.", "When you are reduced to 0 hit points but not killed outright, you can drop to 1 hit point instead. You can't use this feature again until you finish a long rest."),
			Trait("Savage Attacks.", "When you score a critical hit with a melee weapon attack, you can roll one of the weapon's damage dice one additional time and add it to the extra damage of the critical hit.")
		}},

		{"Tiefling", {
			Trait("Darkvision.", "Thanks to your Infernal heritage, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in the darkness, only shades of gray."),
			Trait("Hellish Resisitance.", "You have resistance to fire damage."),
			Trait("Infernal Legacy.", "You know the thaumaturgy cantrip. Once you reach 3rd level, you can cast the hellish rebuke spell once per day as a 2nd-level spell. Once you reach 5th level, you can also cast the darkness spell once per day. Charisma is your spellcasting ability for these spells.")
		}}
	};

	const std::unordered_map<std::string, const std::vector<Trait>> BackgroundFeats = {
		{"Acolyte", {Trait("Shelter of the Faithful.", "As an acolyte, you command the respect of those who share your faith, and you can perform the religious ceremonies of your deity. You and your adventuring companions can expect to receive free healing and care at a temple, shrine, or other established presence of your faith, though you must provide any material components needed for spells. Those who share your religion will support you (but only you) at a modest lifestyle.\n"
													   "You might also have ties to a specific temple dedicated to your chosen deity or pantheon, and you have a residence there. This could be the temple where you used to serve, if you remain on good terms with it, or a temple where you have found a new home. While near your temple, you can call upon the priests for assistance, provided the assistance you ask for is not hazardous and you remain in good standing with your temple.")}},

		{"Charlatan", {Trait("False Identity.", "You have created a second identity that includes documentation, established acquaintances, and disguises that allow you to assume that persona. Additionally, you can forge documents including official papers and personal letters, as long as you have seen an example of the kind of document or the handwriting you are trying to copy.")}},

		{"Criminal", {Trait("Criminal Contact.", "You have a reliable and trustworthy contact who acts as your liaison to a network of other criminals. You know how to get messages to and from your contact, even over great distances; specifically, you know the local messengers, corrupt caravan masters, and seedy sailors who can deliver messages for you.")}},

		{"Spy", {Trait("Criminal Contact.", "You have a reliable and trustworthy contact who acts as your liaison to a network of other criminals. You know how to get messages to and from your contact, even over great distances; specifically, you know the local messengers, corrupt caravan masters, and seedy sailors who can deliver messages for you.")}},

		{"Entertainer", {Trait("By Popular Demand.", "You can always find a place to perform, usually in an inn or tavern but possibly with a circus, at a theater, or even in a noble's court. At such a place, you receive free lodging and food of a modest or comfortable standard (depending on the quality of the establishment), as long as your perform each night. In addition, your performance makes you something of a local figure. When strangers recognize you in a town where you have performed, they typically take a liking to you.")}},

		{"Gladiator", {Trait("By Popular Demand.", "You can always find a place to perform, usually in an inn or tavern but possibly with a circus, at a theater, or even in a noble's court. At such a place, you receive free lodging and food of a modest or comfortable standard (depending on the quality of the establishment), as long as your perform each night. In addition, your performance makes you something of a local figure. When strangers recognize you in a town where you have performed, they typically take a liking to you.")}},

		{"Folk Hero", {Trait("Rustic Hospitality.", "Since you come from the ranks of the common folk, you fit in among them with ease. You can find a place to hide, rest, or recuperate among other commoners, unless you have shown yourself to be a danger to them. They will shield you from the law or anyone else searching for you, though they will not risk their lives for you.")}},

		{"Guild Artisan", {Trait("Guild Membership.", "As an established and respected member of a guild, you can rely on certain benefits that membership provides. Your fellow guild members will provide you with lodging and food if necessary, and pay for your funeral if needed. In some cities and towns, a guildhall offers a central place to meet other members of your profession, which can be a good place to meet potential patrons, allies, or hirelings.\n"
													  "Guilds often wield tremendous political power. If you are accused of a crime, your guild will support you if a good case can be made for your innocence or the crime is justifiable. You can also gain access to powerful political figures through the guild, if you are a member in good standing. Such connections might require the donation of money or magic items to the guild's coffers.\n"
													  "You must pay 5 gp per month to the guild. If you miss payments, you must make up back dues to remain in the guild's good graces.")}},

		{"Guild Merchant", {Trait("Guild Membership.", "As an established and respected member of a guild, you can rely on certain benefits that membership provides. Your fellow guild members will provide you with lodging and food if necessary, and pay for your funeral if needed. In some cities and towns, a guildhall offers a central place to meet other members of your profession, which can be a good place to meet potential patrons, allies, or hirelings.\n"
													   "Guilds often wield tremendous political power. If you are accused of a crime, your guild will support you if a good case can be made for your innocence or the crime is justifiable. You can also gain access to powerful political figures through the guild, if you are a member in good standing. Such connections might require the donation of money or magic items to the guild's coffers.\n"
													   "You must pay 5 gp per month to the guild. If you miss payments, you must make up back dues to remain in the guild's good graces.")}},

		{"Hermit", {Trait("Discovery.", "The quiet seclusion of your extended hermitage gave you access to a unique and powerful discovery. The exact nature of this revelation depends on the nature of your seclusion. It might be a great truth about the cosmos, the deities, the powerful beings of the outer planes, or the forces of nature. It could be a site that no one else has ever seen. You might have uncovered a fact that has been long forgotten, or unearthed some relic of the past that could rewrite history. It might be information that would be damaging to the people who consigned you to exile, and hence the reason for your return to society.")}},

		{"Noble", {Trait("Position of Privilege.", "Thanks to your noble birth, people are inclined to think the best of you. You are welcome in high society, and people assume you have the right to be wherever you are. The common folk make every effort to accommodate you and avoid your displeasure, and other people of high birth treat you as a member of the same social sphere. You can secure an audience with a local noble if you need to."),
				   Trait("Retainers.", "You have the service of three retainers loyal to your family. These retainers can be attendants or messengers, and one might be a majordomo. Your retainers are commoners who can perform mundane tasks for you, but they do not fight for you, will not follow you into obviously dangerous areas (such as dungeons), and will leave if they are frequently endangered or abused.")}},

		{"Knight", {Trait("Retainers.", "You have the service of three retainers loyal to your family. These retainers can be attendants or messengers, and one might be a majordomo. Your retainers are commoners who can perform mundane tasks for you, but they do not fight for you, will not follow you into obviously dangerous areas (such as dungeons), and will leave if they are frequently endangered or abused.")}},

		{"Outlander", {Trait("Wanderer.", "You have an excellent memory for maps and geography, and you can always recall the general layout of terrain, settlements, and other features around you. In addition, you can find food and fresh water for yourself and up to five other people each day, provided that the land offers berries, small game, and so forth.")}},

		{"Sage", {Trait("Researcher.", "When you attempt to learn or recall a piece of lore, if you do not know that information, you often know where and from whom you can obtain it. Usually, this information comes from a library, scriptorium, university, or a sage or other learned person or creature.")}},

		{"Sailor", {Trait("Ship's Passage.", "When you need to, you can secure free passage on a sailing ship for yourself and your adventuring companions. You might sail on the ship you served on, or another ship you have good relations with (perhaps one captained by a former crewmate). Because you're calling in a favor, you can't be certain of a schedule or route that will meet your every need. In return for your free passage, you and your companions are expected to assist the crew during the voyage."),
					Trait("Bad Reputation.", "No matter where you go, people are afraid of you due to your reputation. When you are in a civilized settlement, you can get away with minor criminal offenses, such as refusing to pay for food at a tavern or breaking down doors at a local shop, since most people will not report your activity to the authorities.")}},

		{"Pirate", {Trait("Ship's Passage.", "When you need to, you can secure free passage on a sailing ship for yourself and your adventuring companions. You might sail on the ship you served on, or another ship you have good relations with (perhaps one captained by a former crewmate). Because you're calling in a favor, you can't be certain of a schedule or route that will meet your every need. In return for your free passage, you and your companions are expected to assist the crew during the voyage."),
				    Trait("Bad Reputation.", "No matter where you go, people are afraid of you due to your reputation. When you are in a civilized settlement, you can get away with minor criminal offenses, such as refusing to pay for food at a tavern or breaking down doors at a local shop, since most people will not report your activity to the authorities.")} },

		{"Soldier", {Trait("Military Rank.", "You have a military rank from your career as a soldier. Soldiers loyal to your former military organization still recognize your authority and influence, and they defer to you if they are of a lower rank. You can invoke your rank to exert influence over other soldiers and requisition simple equipment or horses for temporary use. You can also usually gain access to friendly military encampments and fortresses where your rank is recognized.")}},

		{"Urchin", {Trait("City Secrets.", "You know the secret patterns and flow to cities and can find passages through the urban sprawl that others would miss. When you are not in combat, you (and companions you lead) can travel between any two locations in the city twice as fast as your speed would normally allow.")}}
	};

	// TODO: Add the feats that are gained after the first level, and separate the feats gained at each level
	const std::unordered_map<std::string, const std::vector<Trait>> ClassFeats = {
		{"Barbarian", {Trait("Rage.", "In battle, you fight with primal ferocity. On your turn, you can enter a rage as a bonus action.\n"
		                              "While raging, you gain the following benefits if you aren't wearing heavy armor:\n"
		                              "- You have advantage on Strength checks and Strength saving throws.\n"
		                              "- When you make a melee weapon attack using Strength, you gain a bonus to the damage roll that increases as you gain levels as a barbarian, as shown in the Rage Damage column of the Barbarian table in the rulebook.\n"
		                              "- You have resistance to bludgeoning, piercing, and slashing damage.\n"
		                              "If you are able to cast spells, you can't cast them or concentrate on them while raging.\n"
		                              "Your rage lasts for 1 minute. It ends early if you are knocked unconscious or if your turn ends and you haven't attacked a hostile creature since your last turn or taken damage since then. You can also end your rage on your turn as a bonus action.\n"
		                              "Once you have raged the number of times shown for your barbarian level in the Rages column of the Barbarian table in the rulebook, you must finish a long rest before you can rage again."),
	                   Trait("Unarmored Defense.", "While you are not wearing any armor, your Armor Class equals 10 + your Dexterity modifier + your Constitution modifier. You can use a shield and still gain this benefit.")}},

		{"Bard", {Trait("Spellcasting Ability.", "Charisma is your spellcasting for your bard spells. Your magic comes from the heart and soul you pour into the performance of your music or oration. You use your Charisma whenever a spell refers to your spellcasting ability. In addition, you can use your Charisma modifier when setting the saving throw DC for a bard spell you cast and when making an attack roll with one."),
	              Trait("Bardic Inspiration.", "You can inspire others through stirring words or music. To do so, you use a bonus action on your turn to choose one creature other than yourself within 60 feet of you who can hear you. That creature gains one Bardic Inspiration die, a d6.\n"
					                           "Once within the next 10 minutes, the creature can roll the die and add the number rolled to one ability check, attack roll, or saving throw it makes. The creature can wait until after it rolls the d20 before deciding to use the Bardic Inspiration die, but must decide before the DM says whether the roll succeeds or fails. Once the Bardic Inspiration die is rolled, it is lost. A creature can have only one Bardic Inspiration die at a time.\n"
					                           "You can use this feature a number of times equal to your Charisma modifier (a minimum of once). You regain any expended uses when you finish a long rest.\n"
					                           "Your Bardic Inspiration die changes when you reach certain levels in this class. The die becomes a d8 at 5th level, a d10 at 10th level, and a d12 at 15th level.")}},

		{"Cleric", {Trait("Spellcasting Ability.", "Wisdom is your spellcasting ability for your cleric spells. The power of your spells comes from your devotion to your deity. You use your Wisdom whenever a cleric spell refers to your spellcasting ability. In addition, you use your Wisdom modifier when setting the saving throw DC for a cleric spell you cast and when making an attack roll with one."),
	                Trait("Disciple of Life.", "Your healing spells are more effective. Whenever you use a spell of 1st level or higher to restore hit points to a creature, the creature regains additional hit points equal to 2 + the spell's level."),
	                Trait("Warding Flare.", "You can interpose divine light between yourself and an attacking enemy. When you are attacked by a creature within 30 feet of you that you can see, you can use your reaction to impose disadvantage on the attack roll, causing a light to flare before the attacker before it hits or misses. An attacker that can't be blinded is immune to this feature.\n"
				                            "You can use this feature a number of times equal to your Wisdom modifier (a minimum of once). You regain all expended uses when you finish a long rest."),
	                Trait("Wrath of the Storm.", "You can thunderously rebuke attackers. When a creature within 5 feet of you that you can see hits you with an attack, you can use your reaction to cause the creature to make a Dexterity saving throw. The creature takes 2d8 lightning or thunder damage (your choice) on a failed saving throw, and half as much damage on a successful one.\n"
				                                 "You can use this feature a number of times equal to your Wisdom modifier (a minimum of once). You regain all expended uses when you finish a long rest."),
	                Trait("Blessing of the Trickster.", "You can use your action to touch a willing creature other than yourself to give it an advantage on Dexterity (Stealth) checks. This blessing lasts for 1 hour or until you use this feature again."),
	                Trait("War Priest.", "Your god delivers bolts of inspiration to you while you are engaged in battle. When you use the Attack action, you can make one weapon attack as a bonus action.\n"
				                         "You can use this feature a number of times equal to your Wisdom modifier (a minimum of once). You regain all expended uses when you finish a long rest.")}},

		{"Druid", {Trait("Druidic.", "You know Druidic, the secret language of druids. You can speak the language and use it to leave hidden messages. You and others who know this language automatically spot such a message. Others spot the message's presence with a successful DC 15 Wisdom (Perception) check but can't decipher it without magic."),
			       Trait("Spellcasting Ability.", "Wisdom is your spellcasting ability for your druid spells, since your magic draws upon your devotion and attunement to nature. You use your Wisdom whenever a spell refers to your spellcasting ability. In addition, you use your Wisdom modifier when setting the saving throw DC for a druid spell you cast and when making an attack roll with one.")}},

		{"Fighter", {Trait("Second Wind.", "You have a limited well of stamina that you can draw on to protect yourself from harm. On your turn, you can use a bonus reaction to regain hit points equal to 1d10 + your fighter level.\n"
										   "Once you use this feature, you must finish a short or long rest before you can use it again."),
			         Trait("Archery.", "You gain a +2 bonus to attack rolls you make with ranged weapons."),
	                 Trait("Defense.", "While you are wearing armor, you gain a +1 bonus to AC"),
	                 Trait("Dueling.", "When you are wielding a melee weapon in one hand and no other weapons, you gain a +2 bonus to damage rolls with that weapon."),
	                 Trait("Great Weapon Fighting.", "When you roll a 1 or 2 on a damage die for an attack you make with a melee weapon that you are wielding with two hands, you can reroll the die and must use the new roll, even if the new roll is a 1 or a 2. The weapon must have the two-handed or versatile property for you to gain this benefit."),
	                 Trait("Protection.", "When a creature you can see attacks a target other than you that is within 5 feet of you, you can use your reaction to impose disadvantage on the attack roll. You must be wielding a shield."),
	                 Trait("Two-Weapon Fighting.", "When you engage in two-weapon fighting, you can add your ability modifier to the damage of the second attack.")}},

		{"Monk", {Trait("Unarmored Defense.", "While you are wearing no armor and not wielding a shield, your AC equals 10 + your Dexterity modifier + your Wisdom modifier."),
	              Trait("Martial Arts.", "Your practice of martial arts gives you mastery of combat styles that use unarmed strikes and monk weapons, which are shortswords and any simple melee weapons that don't have the two-handed or heavy property.\n"
				                         "You gain the following benefits while you are unarmed or wielding only monk weapons and you aren't wearing armor or wielding a shield:\n"
				                         "- You can use Dexterity instead of Strength for the attack and damage rolls of your unarmed strikes and monk weapons.\n"
				                         "- You can roll a d4 in place of the normal damage on of your unarmed strike or monk weapon. This die changes as you gain monk levels, as shown in the Martial Arts column of the Monk table in the rulebook.\n"
				                         "- When you use the Attack action with an unarmed strike or a monk weapon on your turn, you can make one unarmed strike as a bonus action. For example, if you take the Attack action and attack with a quarter-staff, you can also make an unarmed strike as a bonus action, assuming you haven't already taken a bonus action this turn.\n"
				                         "Certain monasteries use specialized forms of the monk weapons. For example, you might use a club that is two lenghts of wood connected by a short chain (called a nunchaku) or a sickle with a shorter, straighter blade (called a kama). Whatever name you use for a monk weapon, you can use the game statistics provided for the weapon in the rulebook.")}},

		{"Paladin", {Trait("Divine Sense.", "The presence of strong evil registers on your senses like a noxious odor, and powerful good rings like heavenly music in your ears. As an action, you can open your awareness to detect such forces. Until the end of your next turn, you know the location of any celestial, fiend, or undead within 60 feet of you that is not behind total cover. You know the type (celestial, fiend, or undead) of any being whose presence you sense, but not its identity (the vampire Count Strahd von Zarovich, for instance). Within the same radius, you also detect the presence of any place or object that has been consecrated or desecrated, as with the hallow spell.\n"
		                                    "You can use this feature a number of times equal to 1 + your Charisma modifier. When you finish a long rest, you regain all expended uses."),
	                 Trait("Lay on Hands.", "Your blessed touch can heal wounds. You have a pool of healing power that replenishes when you take a long rest. With that pool, you can restore a total number of hit points equal to your Paladin level x 5.\n"
					                        "As an action, you can touch a creature and draw power from the pool to restore a number of hit points to that creature, up to the maximum amount remaining in your pool.\n"
					                        "Alternatively, you can expend 5 hit points from your pool of healing to cure the target of one disease or neutralize one poison affecting it. You can cure multiple diseases or neutralize multiple poisons with a single use of Lay on Hands, expending hit points separately for each one.\n"
					                        "This feature has no effect on undead and constructs.")}},

		{"Ranger", {Trait("Favored Enemy.", "You have significant experience studying, tracking, hunting, and even talking to a certain type of enemy.\n"
		                                    "Choose a type of favored enemy: abberations, beasts, celestials, constructs, dragons, elementals, fey, fiends, giants, monstosities, oozes, plants, or undead. Alternatively, you can select two races of humanoid (such as gnolls and orcs) as favored enemies.\n"
		                                    "You have advantage on Wisdom (Survival) checks to track your favored enemies, as well as on Intelligence checks to recall information about them.\n"
		                                    "When you gain this feature, you also learn one language of your choice that is spoken by your favored enemies, if they speak one at all.\n"
		                                    "You choose one additional favored enemy, as well as an associated language, at 6th and 14th level. As you gain levels, your choices should reflect the types of monsters you have encountered on your adventures."),
	                Trait("Natural Explorer.", "You are particularly familiar with one type of natural environment and are adept at traveling and surviving in such regions. Choose one type of favored terrain: arctic, coast, desert, forest, grassland, mountain, swamp, or the Underdark. When you make an Intelligence or Wisdom check related to your favored terrain, your proficiency bonus is doubled if you are using a skill that you're proficient in.\n"
					                           "While traveling for an hour or more in your favored terrain, you gain the following benefits:\n"
					                           "- Difficult terrain doesn't slow your group's travel.\n"
					                           "- Your group can't become lost except by magical means.\n"
					                           "- Even when you are engaged in another activity while traveling (such as foraging, navigating, or tracking), you remain alert to danger.\n"
					                           "- If you are traveling alone, you can move stealthily at a normal pace.\n"
					                           "- When you forage, you find twice as much food as you normally would.\n"
					                           "- While tracking other creatures, you also learn their exact number, their sizes, and how long ago they passed through the area.\n"
					                           "You choose additional favored terrain types at 6th and 10th level.")}},

		{"Rogue", {Trait("Expertise.", "Choose two of your skill proficiencies, or one of your skill profiencies and your proficiency with thieves' tools. Your proficiency bonus is doubled for any ability check you make that uses either of the chosen proficiencies.\n"
		                               "At 6th level, you can choose two more of you proficiencies (in skills or with thieves' tools) to gain this benefit."),
	               Trait("Sneak Attack.", "You know how to strike subtly and exploit a foe's distraction. Once per turn, you can deal an extra 1d6 damage to one creature you hit with an attack if you have advantage on the attack roll. The attack must use a finesse or a ranged weapon.\n"
				                          "You don't need advantage on the attack roll if another enemy of the target is within 5 feet of it, that enemy isn't incapacitated, and you don't have disadvantage on the attack roll.\n"
				                          "The amount of the extra damage increases as you gain levels in this class, as shown in the Sneak Attack column of the Rogue Table in the rulebook."),
	               Trait("Thieves' Cant.", "During your rogue training you learned a thieves' cant, a secret mix of dialect, jargon, and code that allows you to hide messages in seemingly normal conversation. Only another creature that knows thieves' cant understands such messages. It takes four times longer to convey such a message than it does to speak the same idea plainly.\n"
				                           "In addition, you understand a set of secret signs and symbols used to convey short, simple messages, such as whether an area is dangerous or the territory of a thieves' guild, whether loot is nearby, or whether the people in an area are easy marks or will provide a safe house for thieves on the run.")}},

		{"Sorcerer", {Trait("Spellcasting Ability.", "Charisma is your spellcasting ability for your sorcerer spells, since the power of your magic relies on your ability to project your will into the world. You use your Charisma whenever a spell refers to your spellcasting ability. In addition, you use your Charisma modifier when setting the saving throw DC for a sorcerer spell you cast and when making an attack roll with one."),
	                  Trait("Sorcerous Origin.", "Choose a sorcerous origin, which describes the source of your innate magical power: Draconic Bloodline or Wild Magic, both detailed at the end of the class description in the rulebook.\n"
						                         "Your choice grants you features when you choose it at 1st level and again at 6th, 14th, and 18th level.")}},

		{"Warlock", {Trait("Otherworldly Patron.", "You have struck a bargain with an otherwordly being of your choice: the Archfey, the Fiend, or the Great Old One, each of which is detailed at the end of the class description. Your choice grants you features at 1st level and again at 6th, 10th, and 14th level."),
	                 Trait("Pact Magic.", "Your arcane research and the magic bestowed on your by your patron have given you facility with spells. See the rulebook for rules on casting your spells.")}},

		{"Wizard", {Trait("Spellcasting Ability.", "Intelligence is your spellcasting ability for your wizard spells, since you learn your spells through dedicated study and memorization. You use your Intelligence whenever a spell refers to your spellcasting ability. In addition, you use your Intelligence modifier when setting the saving throw DC for a wizard spell you cast and when making an attack roll with one."),
	                Trait("Arcane Recovery.", "You have learned to regain some of your magical energy by studying your spellbook. Once per day when you finish a short rest, you can choose expended spell slots to recover. The spell slots can have a combined level that is equal to or less than half your wizard level (rounded up), and none of the slots can be 6th level or higher.\n"
						                      "For example, if you're a 4th-level wizard, you can recover up to two levels worth of spell slots. You can recover either a 2nd-level spell slot or two 1st-level spell slots.")}}
	};


	// ======================================================================================
	// Spell Lists
	// ======================================================================================

	// Note: not every class has cantrips
	const std::unordered_map<std::string, std::vector<std::string>> CantripLists = {
		{"Bard", {"blade ward", "dancing lights", "friends", "light", "mage hand", "mending", "message", "minor illusion", "prestidigitation", "true strike", "vicious mockery"}},
		{"Cleric", {"guidance", "light", "mending", "resistance", "sacred flame", "spare the dying", "thaumaturgy"}},
		{"Druid", {"druidcraft", "guidance", "mending", "poison spray", "produce flame", "resistance", "shillelagh", "thorn whip"}},
		{"Sorcerer", {"acid splash", "blade ward", "chill touch", "dancing lights", "fire bolt", "friends", "light", "mage hand", "mending", "message", "minor illusion", "poison spray", "prestidigitation", "ray of frost", "shocking grasp", "true strike"}},
		{"Warlock", {"blade ward", "chill touch", "eldritch blast", "friends", "mage hand", "minor illusion", "poison spray", "prestidigitation", "true strike"}},
		{"Wizard", {"acid splash", "blade ward", "chill touch", "dancing lights", "fire bolt", "friends", "light", "mage hand", "mending", "message", "minor illusion", "poison spray", "prestidigitation", "ray of frost", "shocking grasp", "true strike"}}
	};
	
	// Note: Only some classes have spellcasting ability
	// Note: Paladins and rangers do not learn spells until they reach level 2
	// TODO: Add spells spells higher than 1st-level and separate the spells for each class by level
	const std::unordered_map<std::string, std::vector<std::string>> SpellLists = {
		{"Bard", {"animal friendship", "bane", "charm person", "comprehend languages", "cure wounds", "detect magic", "disguise self", "dissonant whispers", "faerie fire", "feather fall", "healing word", "heroism", "identify", "illusory script", "longstrider", "silent image", "sleep", "speak with animals", "Tahsa's hideous laughter", "thunderwave", "unseen servant"}},
		{"Cleric", {"bane", "bless", "command", "create or destroy water", "cure wounds", "detect evil and good", "detect magic", "detect poison and disease", "guiding bolt", "healing word", "inflict wounds", "protection from evil and good", "purify food and drink", "sanctuary", "shield of faith"}},
		{"Druid", {"animal friendship", "charm person", "create or destroy water", "cure wounds", "detect magic", "detect poison or disease", "entangle", "faeirie fire", "fog cloud", "goodberry", "healing word", "jump", "longstrider", "purify food and drink", "speak with animals", "thunderwave"}},
		{"Paladin", {"bless", "command", "compelled duel", "cure wounds", "detect evil and good", "detect magic", "detect poison and disease", "divine favor", "heroism", "protection from evil and good", "purify food and drink", "searing smite", "shield of faith", "thunderous smite", "wrathful smite"}},
		{"Ranger", {"alarm", "animal friendship", "cure wounds", "detect magic", "detect poison and disease", "ensnaring strike", "fog cloud", "goodberry", "hail of thorns", "hunter's mark", "jump", "longstrider", "speak with animals"}},
		{"Sorcerer", {"burning hands", "charm person", "chromatic orb", "color spray", "comprehend languages", "detect magic", "disguise self", "expeditious retreat", "false life", "feather fall", "fog cloud", "jump", "mage armor", "magic missile", "ray of sickness", "shield", "silent image", "sleep", "thunderwave", "witch bolt"}},
		{"Warlock", {"armor of Agathys", "arms of Hadar", "charm person", "comprehend languages", "expeditious retreat", "hellish rebuke", "hex", "illusory script", "protection from evil and good", "unseen servant", "witch bolt"}},
		{"Wizard", {"alarm", "burning hands", "charm person", "chromatic orb", "color spray", "comprehend languages", "detect magic", "disguise self", "expeditious retreat", "false life", "feather fall", "find familiar", "fog cloud", "grease", "identify", "illusory script", "jump", "longstrider", "mage armor", "magic missile", "protection from evil and good", "ray of sickness", "shield", "silent image", "sleep", "Tasha's hideous laughter", "Tenser's floating disk", "thunderwave", "unseen servant", "witch bolt"}}
	};
}
