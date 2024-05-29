#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>
#include "cyberkolya.h"
#include "legacy_database.h"
#include "my_database.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main() {

	_setmode(_fileno(stdout), _O_U16TEXT);
	//LegacyDatabase database;
	MyDatabase database;
	Cyberkolya cyberkolya(database);
	cyberkolya.read_from_files("../database/users.tsv",
		{"../database/inside.tsv", "../database/teamtardis.tsv", "../database/insidenot.tsv", 
		"../database/sfedu.tsv",	"../database/mmcs.tsv" });

	//std::priority_queue<std::pair<AbstractDatabase::Post, int>, 
	//	std::vector<std::pair<AbstractDatabase::Post, int>>, 
	//	MyDatabase::PostComparator> postsByLikes; // пост - количество лайков
	//postsByLikes.push(std::make_pair(AbstractDatabase::Post{ 1, 123, 3, 1714676192, 0, 0 },3));
	//postsByLikes.push(std::make_pair(AbstractDatabase::Post{ 2, 123, 3, 1714676192, 0, 0 },5));
	//postsByLikes.push(std::make_pair(AbstractDatabase::Post{ 5, 123, 3, 1714676192, 0, 0 },565));
	/*AbstractDatabase::Post post{ 1, 123, 3, 1714676192, 0, 0 };
	database.insert_post(post);
	AbstractDatabase::Post post2{ 2, 123, 2, 1714676193, 0, 0 };
	database.insert_post(post2);
	AbstractDatabase::Post post3{ 1, 124, 1, 1714676194, 0, 0 };
	database.insert_post(post3);
	database.top_k_authors_by_likes(10, -88704999, 1704056400, 1735678800);*/
	std::wstringstream cmd(LR"(
		insert_user 1 Александр Иванов
		insert_user 2 Петр		Дуров
		insert_user 3 Павел		Сидоров
		insert_post 1 123 3 1714676192 0 0
		insert_post 2 123 2 1714676193 0 0
		insert_post 1 124 1 1714676194 0 0
		like_post 123 1
		like_post 123 1
		like_post 123 1
		like_post 123 1
		like_post 123 2
		like_post 124 1
		like_post 124 1
		get_user 1
		get_user 2
		get_user 3
		top_k_posts_by_likes 10 123 1704056400 1735678800
		top_k_authors_by_likes 10 123 1704056400 1735678800
		top_k_posts_by_likes 10 -88704999 1704056400 1735678800
		top_k_authors_by_likes 10 -88704999 1704056400 1735678800
		help)");
	while (!cmd.eof()) {
		cyberkolya.process_event(cmd, std::wcout);
	}
	while (!std::wcin.eof() && std::wcin.good()) {
		std::wcout << "admin$: ";
		cyberkolya.process_event(std::wcin, std::wcout);
	}
}

/*
legacy
OK
1532 ms.
OK
631 ms.
OK
596 ms.
OK
898 ms.
OK
866 ms.
OK
866 ms.
OK
1144 ms.
OK
890 ms.
OK
804 ms.
OK
788 ms.
OK
868 ms.
OK
638 ms.
OK
661 ms.
1       РђР»РµРєСЃР°РЅРґСЂ      РРІР°РЅРѕРІ
3569 ms.
2       РџРµС‚СЂ        Р”СѓСЂРѕРІ
4561 ms.
3       РџР°РІРµР»      РЎРёРґРѕСЂРѕРІ
3166 ms.
1. ID: 1, likes: 4
2. ID: 2, likes: 1
12232 ms.
1. User: 3      РџР°РІРµР»      РЎРёРґРѕСЂРѕРІ, likes: 4
2. User: 2      РџРµС‚СЂ        Р”СѓСЂРѕРІ, likes: 1
6993 ms.
1. ID: 1859, likes: 207
2. ID: 1900, likes: 177
3. ID: 1848, likes: 112
4. ID: 1852, likes: 82
5. ID: 1896, likes: 53
6. ID: 1881, likes: 48
7. ID: 1886, likes: 43
8. ID: 1829, likes: 42
9. ID: 1947, likes: 41
10. ID: 1811, likes: 41
28150 ms.
1. User: 34041162       Эдуард  Сариев, likes: 384
2. User: 17808715       Андрей  Руденец, likes: 213
3. User: 50168542       Владислав       Назаренко, likes: 182
4. User: 137509477      Михаил  Карякин, likes: 177
5. User: -88704999      Мехмат_ЮФУ      group, likes: 177
6. User: 7503745        Светлана        Лазарева, likes: 108
7. User: 7550797        Яков    Ерусалимский, likes: 96
8. User: 80684434       Виктор  Сухов, likes: 38
9. User: 36762561       Роман   Мнухин, likes: 30
38125 ms.
Доступные команды:
get_user        userId
get_post        ownerId postId
insert_user     id firstName LastName
insert_post     id ownerId fromId unixDate likes reposts
delete_post     ownerId postId
like_post       ownerId postId
unlike_post     ownerId postId
repost_post     ownerId postId
top_k_post_by_likes             k       ownerId dateBegin       dateEnd
top_k_post_by_reposts           k       ownerId dateBegin       dateEnd
top_k_authors_by_likes          k       ownerId dateBegin       dateEnd
top_k_authors_by_reports        k       ownerId dateBegin       dateEnd
48314 ms.
admin$:   insert_post 344 7550797 7550797 3343445 45 5
OK
607 ms.
*/

