#include <list>
#include <vector>
#include "CppUnitTest.h"
#include "my_list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListTests
{
	class Elem {
		int data;
		uint32_t watch;
		static size_t elem_counter;
		void check() const { Assert::IsTrue(watch == 0xDEADBEEF, L"Повреждение памяти!! (Обращение к неинициализированному экземпляру класса Elem)"); }
	public:
		Elem(const Elem& other) {
			other.check();
			data = other.data;
			watch = other.watch;
			++elem_counter;
		}
		Elem& operator=(const Elem& other) {
			if (!(*this == other))
			{
				check();
				other.check();
				data = other.data;
				watch = other.watch;
			}
			return *this;
		}
		explicit Elem(int value) : data(value), watch(0xDEADBEEF) { ++elem_counter; }
		Elem(Elem&& e) noexcept { e.check(); data = e.data; watch = e.watch; ++elem_counter; }
		Elem& operator=(Elem&& e) noexcept { check(); e.check(); data = e.data; watch = e.watch; }
		bool operator==(const Elem& e) const { check(); e.check(); return data == e.data; }
		~Elem() { check(); watch = 0; --elem_counter; }
		static size_t count() { return elem_counter; }
	};
	size_t Elem::elem_counter = 0;

	//  Для того, чтобы выполнить тестирование одного из указанных контейнеров (std::list или MyList),
	//  должна быть раскомментирована одна из следующих строк:
	//template<typename T> using ContainerTemplate = std::list<T>;
	template<typename T> using ContainerTemplate = MyList<T>;

	TEST_CLASS(ComplexTypeTests)
	{

	public:

		TEST_METHOD(IteratorTests)
		{
			ContainerTemplate<int> list{ 3, 4, 8, 5, 2, 13, 20 };
			list.push_back(10);
			Assert::IsTrue(list.end() == ++--list.end(), L"++--list.end() должен возвращать list.end()");
			Assert::AreEqual(10, *(--list.end()), L"--list.end() должен возвращать последний элемент");
		}

		TEST_METHOD(StringTests)
		{
			ContainerTemplate<std::string> list{ "123", "AAAAAAAA", "abc", "cde" };
			std::vector<std::string> expected1{ "123", "AAAAAAAA", "abc", "cde" };

			Assert::AreEqual(4ull, list.size(), L"Неправильно считается количество строковых элементов");
			Assert::IsTrue(std::equal(list.begin(), list.end(), expected1.begin(), expected1.end()), L"Неправильный порядок строковых элементов");
			//Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected1.rbegin(), expected1.rend()), L"Неправильный порядок строковых элементов");

			for (const auto& str : expected1)
				list.erase(std::find(list.begin(), list.end(), str));

			Assert::AreEqual(0ull, list.size(), L"Список не пуст после удаления всех элементов");
			for (const auto& elem : list)
				Assert::Fail(L"Что-то лежит в списке после удаления всех элементов");

			list.push_back("test-1");
			list.push_back("test-2");
			list.push_back("test-4");
			std::vector<std::string> expected2{ "test-1", "test-2", "test-4" };
			Assert::IsTrue(std::equal(list.begin(), list.end(), expected2.begin(), expected2.end()), L"Неправильный порядок строковых элементов");
			//Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected2.rbegin(), expected2.rend()), L"Неправильный порядок строковых элементов");
		}

		TEST_METHOD(ElemTests)
		{
			size_t init_count = Elem::count();
			{
				ContainerTemplate<Elem> list;
				Assert::AreEqual(0ull, Elem::count() - init_count, L"Создан лишний экземпляр класса Elem");

				for (const auto& elem : list)
					Assert::Fail(L"Что-то лежит в пустом списке");

				list.push_back(Elem(40));
				list.push_back(Elem(75));
				list.push_front(Elem(50));
				list.push_back(Elem(23));
				list.push_back(Elem(87));
				Assert::IsTrue(Elem::count() - init_count == 5, L"Создан лишний экземпляр класса Elem");
				list.erase(std::find(list.begin(), list.end(), Elem(75)));
				Assert::IsTrue(Elem::count() - init_count == 4, L"Неправильно работает удаление элементов списка");
			}
			Assert::IsTrue(Elem::count() - init_count == 0, L"Утечка памяти!!");


			
		}

		TEST_METHOD(MyTests) {

			ContainerTemplate<std::string> list{ "123", "AAAAAAAA", "abc", "cde" };

			Assert::AreEqual(static_cast<std::string>("123"), list.front());
			Assert::AreEqual(static_cast<std::string>("cde"), list.back());
			Assert::IsFalse(list.empty());
			ContainerTemplate<std::string> li;
			Assert::IsTrue(li.empty());
			li.push_back("99");
			Assert::IsFalse(li.empty());
			Assert::AreEqual(static_cast<size_t>(1), li.size());

			std::vector<std::string> b{ "b1","b2","b3","b4","b5","b6","b7","b8","b9","b10" };
			for(int i = 0;i < 10;i++)
				li.push_back(b[i]);
			Assert::AreEqual(static_cast<size_t>(11), li.size());

			Assert::AreEqual(static_cast<std::string>("99"), li.front());
			Assert::AreEqual(static_cast<std::string>("b10"), li.back());

			std::vector<std::string> fr{ "f1","f2","f3","f4","f5"};
			for (int i = 0;i < 5;i++)
				li.push_front(fr[i]);
			Assert::AreEqual(static_cast<size_t>(16), li.size());

			Assert::AreEqual(static_cast<std::string>("f5"), li.front());
			Assert::AreEqual(static_cast<std::string>("b10"), li.back());

			li.pop_back();
			Assert::AreEqual(static_cast<std::string>("b9"), li.back());

			li.pop_back();
			Assert::AreEqual(static_cast<std::string>("b8"), li.back());

			li.pop_front();
			Assert::AreEqual(static_cast<std::string>("f4"), li.front());

			li.pop_front();
			Assert::AreEqual(static_cast<std::string>("f3"), li.front());

			li.insert(std::find(li.begin(), li.end(), "99"), "100");
			Assert::AreEqual(static_cast<size_t>(13), li.size());
			

			std::vector<std::string> expected2{ "123", "AAAAAAAA", "abc", "cde" };

			li.swap(list);

			Assert::IsTrue(std::equal(li.begin(), li.end(), expected2.begin(), expected2.end()));


			li.clear();

			Assert::IsTrue(li.empty());

			MyList<int> l3;
			MyList<double> l4;
			Assert::AreEqual(static_cast<unsigned int>(0), l3.count_of_pos());
			Assert::AreEqual(static_cast<unsigned int>(0), l4.count_of_pos());

			l3.push_back(1);
			l3.push_back(9);
			Assert::AreEqual(static_cast<unsigned int>(2), l3.count_of_pos());

			l3.push_back(-1);
			l3.push_back(-9);
			Assert::AreEqual(static_cast<unsigned int>(2), l3.count_of_pos());

			l4.push_back(-1.9);
			l4.push_back(-9.999);
			Assert::AreEqual(static_cast<unsigned int>(0), l4.count_of_pos());

			l4.push_back(1.9);
			l4.push_back(9.9);
			Assert::AreEqual(static_cast<unsigned int>(2), l4.count_of_pos());


			l3 = {1,2,3,4,5};
			l4 = {1.8,2.8,3.8,4.8,5.8};

			std::tuple<int, unsigned int> res3 = l3.max_elem_count();
			std::tuple<double, unsigned int> res4 = l4.max_elem_count();

			Assert::AreEqual(5, std::get<0>(res3));
			Assert::AreEqual(static_cast<unsigned int>(1), std::get<1>(res3));

			Assert::AreEqual(5.8, std::get<0>(res4));
			Assert::AreEqual(static_cast<unsigned int>(1), std::get<1>(res4));


			l3 = { -11,-111,-11,-12,-22 };
			l4 = { -1.2,-1,-1,-1,-2.2,-2.2};

			res3 = l3.max_elem_count();
			res4 = l4.max_elem_count();

			Assert::AreEqual(-11, std::get<0>(res3));
			Assert::AreEqual(static_cast<unsigned int>(2), std::get<1>(res3));

			Assert::AreEqual(-1.0, std::get<0>(res4));
			Assert::AreEqual(static_cast<unsigned int>(3), std::get<1>(res4));

			//void split_on_positivity(MyList& pos, MyList& neg)

			MyList<int> pos;
			MyList<int> neg;

			l3 = { 2,4,-34,4,-12345,42,11,-24 };
			
			std::vector<int> expectedpos{ 2,4,4,42,11 };
			std::vector<int> expectedneg{ -34,-12345,-24 };

			l3.split_on_positivity(pos, neg);

			Assert::IsTrue(std::equal(pos.begin(), pos.end(), expectedpos.begin(), expectedpos.end()));

			Assert::IsTrue(std::equal(neg.begin(), neg.end(), expectedneg.begin(), expectedneg.end()));


			MyList<double> pos2;
			MyList<double> neg2;

			l4 = { 2.5,4,-34.001,4.5,-12345,42.99,11,-24.8,0 };

			std::vector<double> expectedpos2{ 2.5,4,4.5,42.99,11,0 };
			std::vector<double> expectedneg2{ -34.001,-12345,-24.8 };

			l4.split_on_positivity(pos2, neg2);

			Assert::IsTrue(std::equal(pos2.begin(), pos2.end(), expectedpos2.begin(), expectedpos2.end()));

			Assert::IsTrue(std::equal(neg2.begin(), neg2.end(), expectedneg2.begin(), expectedneg2.end()));

		}
	};
}
