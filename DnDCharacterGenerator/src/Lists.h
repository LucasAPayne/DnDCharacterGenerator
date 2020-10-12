#pragma once

#include <array>
#include <string>
#include <unordered_map>
#include <utility> // std::pair
#include <vector>

namespace dnd {

	// Constants
	const int NumClasses = 12;
	const int NumRaces = 11;
	const int NumEthnicities = 9;
	const int NumGenders = 2;
	const int NumBackgrounds = 18;
	const int NumAlignments = 9;
	const int NumLanguages = 15;
	const int NumLevels = 21;

	// ======================================================================================
	// Small Lists
	// ======================================================================================

	const std::array<std::string, NumClasses> Classes = {
		"Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"
	};

	const std::array<std::string, NumRaces> Races = {
		"Dwarf", "Hill Dwarf", "Mountain Dwarf", "Elf", "High Elf", "Wood Elf", "Dark Elf (Drow)", "Halfling", "Lightfoot Halfling", "Stout Halfling", "Human"
	};

	const std::array<std::string, NumEthnicities> Ethnicities = {
		"Calishite", "Chondathan", "Damaran", "Illuskan", "Mulan", "Rashemi", "Shou", "Tethyrian", "Turami"
	};

	const std::array<std::string, NumGenders> Genders = {
		"Male", "Female"
	};

	// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
	const std::array<std::string, NumBackgrounds> Backgrounds = {
		"Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan", "Guild Merchant", "Hermit", "Knight",
		"Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier", "Spy", "Urchin"
	};

	const std::array<std::string, NumAlignments> Alignments = {
		"Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral", "Lawful Evil", "Neutral Evil", "Chaotic Evil"
	};

	// Common is not a possible language because every character already knows it
	std::array<std::string, NumLanguages> Languages = {
		"Elvish", "Dwarvish", "Giant", "Gnomish", "Goblin", "Halfling", "Orc",                               // Common Languages
		"Abyssal", "Celestial", "Draconic", "Deep Speech", "Infernal", "Primordial", "Sylvan", "Undercommon" // Exotic Languages
	};

	// First entry null so that expForLevel[1] is how much exp is required for level one, etc.
	const std::array<int, NumLevels> ExpForLevel = {
		 NULL, 0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000
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
		}}
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
		}}
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

	const std::unordered_map <std::string, const std::vector<std::string>> Flaws = {
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

}