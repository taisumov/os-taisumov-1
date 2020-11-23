#include <iostream>
#include <windows.h>

using namespace std;

void PrintMenu() {
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 1 | вывод списка дисков                                        |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 2 | вывод информации о диске и размер свободного пространства  |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 3 | создание и удаление заданных каталогов                     |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 4 | создание в указанном каталоге                              |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 5 | копирование и перемещение файлов между каталогами          |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 6 | анализ и изменение атрибутов файлов                        |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
	cout << "| 0 | Выход из программы                                         |" << endl;
	cout << "+---+------------------------------------------------------------+" << endl;
}

void PrintMenuAttributes() {
	cout << "+---+--------------------------------------------+" << endl;
	cout << "| 1 | вывод информации об атрибутах              |" << endl;
	cout << "+---+--------------------------------------------+" << endl;
	cout << "| 2 | изменение информации об атрибутах          |" << endl;
	cout << "+---+--------------------------------------------+" << endl;
	cout << "| 3 | вывод информации о файле по дескриптору    |" << endl;
	cout << "+---+--------------------------------------------+" << endl;
	cout << "| 4 | информация о системном времени             |" << endl;
	cout << "+---+--------------------------------------------+" << endl;
	cout << "| 5 | изменение системного времени               |" << endl;
	cout << "+---+--------------------------------------------+" << endl;
}

int main() {
	system("chcp 1251");

	//ПЕРЕМЕННЫЕ, ИСПОЛЬЗУЕМЫЕ В ОСНОВНОМ КОДЕ

	//Первый пункт - вывод списка дисков

	int menu;
	int temp;
	int n;

	//Второй пункт - вывод информации о диске

	string disk_name;
	wstring w_string;
	
	LPCWSTR name;
	LPCWSTR direct_name;
	LPCWSTR file_name;
	UINT x;

	WCHAR lpVolumeNameBuffer[MAX_PATH + 1];
	DWORD lpVolumeSerialNumber = 0;
	DWORD lpMaximumComponentLength = 0;
	DWORD lpFileSystemFlags = 0;
	WCHAR lpFileSystemNameBuffer[MAX_PATH + 1];

	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD numberOfFreeClusters;	
	DWORD totalNumberOfClusters;

	//Третий пункт - создание и удаление заданных каталогов

	//   ----//----

	//Четвертый пункт - создание в указанном каталоге
	
	//   ----//----

	//Пятый пункт - копирование и перемещение файлов между каталогами

	string disk_name2;

	wstring w_string_2;

	LPCWSTR firstFile;
	LPCWSTR secondFile;

	int moveFileEx_temp;

	//Шестой пункт - анализ и изменение атрибутов файлов

	DWORD attribute;
	DWORD setAttr;

	LPCSTR fileLPC;

	BY_HANDLE_FILE_INFORMATION lpFileInformation;

	HANDLE fileT;

	FILETIME timeCreate, timeLastAccess, timeLastWrite;
	FILETIME fileTime;

	SYSTEMTIME time;
	SYSTEMTIME systemTime;

	//ОСНОВНОЙ КОД
	do {

		system("cls");
		PrintMenu();

		cin >> menu;
		system("cls");

		switch (menu) {
		case 1: //Первый пункт - вывод списка дисков

			cout << "Список доступных дисков:" << endl;

			temp = GetLogicalDrives();

			for (int x = 0; x < 26; x++)
			{
				n = ((temp >> x) & 1);
				if (n) 
				{
					cout << "- " << (char)(65 + x) << ":\\" << endl;
				}
			}

			system("pause");
			break;

		case 2: //Второй пункт - вывод информации о диске

			//GetDriveType

			cout << "Введите название диска (пример: c:\\): ";
			cin >> disk_name;

			w_string = wstring(disk_name.begin(), disk_name.end());
			name = w_string.c_str();
			x = GetDriveType(name);

			if (x == DRIVE_UNKNOWN) cout <<     "- UNKNOWN           (Неизвестный тип)" << endl;
			if (x == DRIVE_NO_ROOT_DIR) cout << "- DRIVE NO ROOT DIR (Неправильный путь)" << endl;
			if (x == DRIVE_REMOVABLE) cout <<   "- REMOVABLE         (Съёмный диск)" << endl;
			if (x == DRIVE_FIXED) cout <<       "- FIXED             (Фиксированный диск)" << endl;
			if (x == DRIVE_REMOTE) cout <<      "- REMOTE            (Удалённый диск)" << endl;
			if (x == DRIVE_CDROM) cout <<       "- CDROM             (CD-ROM диск)" << endl;
			if (x == DRIVE_RAMDISK) cout <<     "- RAMDISK           (RAM диск)" << endl;


			//GetVolumeInfomation

			if (!GetVolumeInformation(name, lpVolumeNameBuffer, sizeof(lpVolumeNameBuffer), &lpVolumeSerialNumber,
									 &lpMaximumComponentLength, &lpFileSystemFlags,
									 lpFileSystemNameBuffer, sizeof(lpFileSystemNameBuffer)))
			{
				cout << "Ошибка. Не удалось обработать запрос" << endl;
			}
			else {
				cout << endl << "Название указанного диска: " << lpVolumeNameBuffer << endl;
				cout << "Cерийный номер диска:      " << hex << lpVolumeSerialNumber << endl;
				cout << "Максимальная длина файла:  " << dec << lpMaximumComponentLength << endl;
				cout << "Опции файловой системой:   " << oct << lpFileSystemFlags << endl;
				cout << "Имя файловой системы:      " << lpFileSystemNameBuffer << endl;
			}

			//GetFreeDiskSpace

			if (GetDiskFreeSpace(name, &sectorsPerCluster, &bytesPerSector,
				&numberOfFreeClusters, &totalNumberOfClusters)) {
				cout << endl << "- Число секторов в кластере: " << sectorsPerCluster << endl;
				cout <<         "- Число байт в секторе: " << bytesPerSector << endl;
				cout <<         "- Число свободных кластеров: " << numberOfFreeClusters << endl;
				cout <<         "- Общее число кластеров: " << totalNumberOfClusters << endl;
			}

			system("pause");
			break;

		case 3: //Третий пункт - создание и удаление заданных каталогов

			cout << "+---+-------------------+" << endl;
			cout << "| 1 | создание каталога |" << endl;
			cout << "+---+-------------------+" << endl;
			cout << "| 2 | удаление каталога |" << endl;
			cout << "+---+-------------------+" << endl;

			cin >> menu;
			system("cls");

			switch (menu) {
			case 1:
				cout << "Введите имя каталога (пример: c:\\folder): ";
				cin >> disk_name;

				//CreateDirectory

				w_string = wstring(disk_name.begin(), disk_name.end());
				direct_name = w_string.c_str();
				if (!CreateDirectory(direct_name, nullptr)) {
					cout << "Каталог не удалось создать! Ошибка." << endl;
				}
				else {
					cout << "Каталог создан." << endl;
				}

				system("pause");
				break;

			case 2:

				cout << "Введите имя каталога (пример: c:\\folder): ";
				cin >> disk_name;

				//RemoveDirectory

				w_string = wstring(disk_name.begin(), disk_name.end());
				direct_name = w_string.c_str();

				if (!RemoveDirectory(direct_name)) {
					cout << "Каталог не удалось удалить! Ошибка." << endl;
				}
				else {
					cout << "Каталог удален." << endl;
				}

				system("pause");
				break;

			}

			break;

		case 4: //Четвертый пункт - создание в указанном каталоге

			cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
			cin >> disk_name;

			//CreateFile

			w_string = wstring(disk_name.begin(), disk_name.end());
			file_name = w_string.c_str();
			if (CreateFile(file_name, GENERIC_WRITE | GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
				nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) == INVALID_HANDLE_VALUE) {
				cout << "Файл не удалось создать. Код ошибки: " << GetLastError();
			}
			else {
				cout << "Файл успешно создан." << endl;
			}

			system("pause");
			break;

		case 5: //Пятый пункт - копирование и перемещение файлов между каталогами

			cout << "+---+--------------------------------+" << endl;
			cout << "| 1 | копировать файл                |\n";
			cout << "+---+--------------------------------+" << endl;
			cout << "| 2 | переместить файл               |\n";
			cout << "+---+--------------------------------+" << endl;
			cout << "| 3 | переместить файл (с проверкой) |\n";
			cout << "+---+--------------------------------+" << endl;

			cin >> menu;
			system("cls");

			switch (menu) {
			case 1:

				cout << "Введите имя файла-источника (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;
				cout << "Введите имя файла-копии: ";
				cin >> disk_name2;

				//CopyFile

				w_string = wstring(disk_name.begin(), disk_name.end());
				firstFile = w_string.c_str();
				w_string_2 = wstring(disk_name2.begin(), disk_name2.end());
				secondFile = w_string_2.c_str();

				if (CopyFile(firstFile, secondFile, false))
				{
					cout << "Файл успешно скопирован." << endl;
				}
				else {
					cout << "Ошибка! Не удалось скопировать файл. Код ошибки: " << GetLastError() << endl;
				}

				system("pause");
				break;

			case 2:

				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;
				cout << "Введите адрес назначения (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name2;

				//MoveFile

				w_string = wstring(disk_name.begin(), disk_name.end());
				firstFile = w_string.c_str();
				w_string_2 = wstring(disk_name2.begin(), disk_name2.end());
				secondFile = w_string_2.c_str();

				if (MoveFile(firstFile, secondFile)) {
					cout << "Файл успешно перемещен." << endl;
				}
				else {
					cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
				}

				system("pause");
				break;

			case 3:

				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;
				cout << "Введите адрес назначения (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name2;

				//MoveFileEx

				w_string = wstring(disk_name.begin(), disk_name.end());
				firstFile = w_string.c_str();
				w_string_2 = wstring(disk_name2.begin(), disk_name2.end());
				secondFile = w_string_2.c_str();

				moveFileEx_temp = 0;

				if (MoveFileEx(firstFile, secondFile, NULL)) {
					cout << "Файл или каталог успешно перемещен!" << endl;
				}
				else if (GetLastError() == 183) {
					cout << "Уже существует такой файл в данном каталоге. Заменить его?" << endl;
					cout << "+---+-----+" << endl;
					cout << "| 1 | Да  |" << endl;
					cout << "+---+-----+" << endl;
					cout << "| 0 | Нет |" << endl;
					cout << "+---+-----+" << endl;

					cin >> moveFileEx_temp;
					system("cls");

					if (moveFileEx_temp)
					{
						if (MoveFileEx(firstFile, secondFile, MOVEFILE_REPLACE_EXISTING))
						{
							cout << "Файл или каталог успешно перемещен!" << endl;
						}
						else {
							cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
						}
					}
				}
				else {
					cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
				}

				system("pause");
				break;
			}

			system("pause");
			break;

		case 6: //Шестой пункт - анализ и изменение атрибутов файлов

			PrintMenuAttributes();
			cin >> menu;
			system("cls");
			switch (menu) {
			case 1:

				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;

				//GetFileAttributes

				w_string = wstring(disk_name.begin(), disk_name.end());
				file_name = w_string.c_str();
				attribute = GetFileAttributes(file_name);

				if (attribute == 0) {
					cout << "Ошибка! Не удалось получить атрибуты файла." << endl;
				}
				else if (attribute == -1) {
					cout << "Ошибка! Файл не найден." << endl;
				}
				else {
					cout << "Атрибуты файла (" << attribute << "):" << endl;
					if (FILE_ATTRIBUTE_ARCHIVE & attribute) cout <<    "- Архивный файл" << endl;
					if (FILE_ATTRIBUTE_COMPRESSED & attribute) cout << "- Сжатый файл" << endl;
					if (FILE_ATTRIBUTE_DIRECTORY & attribute) cout <<  "- Каталог" << endl;
					if (FILE_ATTRIBUTE_HIDDEN & attribute) cout <<     "- Скрытый файл или каталог" << endl;
					if (FILE_ATTRIBUTE_NORMAL & attribute) cout <<     "- Файл не имеет атрибутов" << endl;
					if (FILE_ATTRIBUTE_READONLY & attribute) cout <<   "- Файл только для чтения" << endl;
				}

				system("pause");
				break;

			case 2:

				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;

				//SetFileAttributes

				w_string = wstring(disk_name.begin(), disk_name.end());
				file_name = w_string.c_str();

				cout << "Изменить атрибут файла на:" << endl;
				cout << "+---+-------------------------+" << endl;
				cout << "| 1 | Архивный файл           |" << endl;
				cout << "+---+-------------------------+" << endl;
				cout << "| 2 | Скрытый файл            |" << endl;
				cout << "+---+-------------------------+" << endl;
				cout << "| 3 | Файл без атрибутов      |" << endl;
				cout << "+---+-------------------------+" << endl;
				cout << "| 4 | Файл только для чтения  |" << endl;
				cout << "+---+-------------------------+" << endl;
				cout << "| 5 | Системный файл          |" << endl;
				cout << "+---+-------------------------+" << endl;

				cin >> setAttr;
				system("cls");

				switch (setAttr) {
				case 1:
					if (SetFileAttributes(file_name,
						FILE_ATTRIBUTE_ARCHIVE)) {
						cout << "Атрибут файла успешно изменен!" << endl;
					}
					else {
						cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
					}
					break;
				case 2:
					if (SetFileAttributes(file_name,
						FILE_ATTRIBUTE_HIDDEN)) {
						cout << "Атрибут файла успешно изменен!" << endl;
					}
					else {
						cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
					}
					break;
				case 3:
					if (SetFileAttributes(file_name,
						FILE_ATTRIBUTE_NORMAL)) {
						cout << "Атрибут файла успешно изменен!" << endl;
					}
					else {
						cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
					}
					break;
				case 4:
					if (SetFileAttributes(file_name,
						FILE_ATTRIBUTE_READONLY)) {
						cout << "Атрибут файла успешно изменен!" << endl;
					}
					else {
						cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
					}
					break;
				case 5:
					if (SetFileAttributes(file_name,
						FILE_ATTRIBUTE_SYSTEM)) {
						cout << "Атрибут файла успешно изменен!" << endl;
					}
					else {
						cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
					}
					break;
				}

				system("pause");
				break;
			case 3:
				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;

				//GetFileInformationByHandle

				fileLPC = disk_name.c_str();
				fileT = CreateFileA(fileLPC, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
					nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (GetFileInformationByHandle(fileT, &lpFileInformation)) {
					cout << "Информация о файле по дескриптору: " << hex
						<< lpFileInformation.dwVolumeSerialNumber << endl;
				}
				else {
					cout << "Ошибка! Не удалось получить информацию о файле. Код ошибки: " << GetLastError() << endl;
				}

				system("pause");
				break;
			case 4:
				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;

				//GetFileTime

				fileLPC = disk_name.c_str();
				fileT = CreateFileA(fileLPC, GENERIC_READ | GENERIC_WRITE,
										FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, 
										CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (GetFileTime(fileT, &timeCreate, &timeLastAccess, &timeLastWrite))
				{
					FileTimeToSystemTime(&timeCreate, &time);
					cout << "Дата и время создания файла:                " <<
						time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour + 3 << ":" <<
						time.wMinute << ":" << time.wSecond << endl;
					FileTimeToSystemTime(&timeLastAccess, &time);
					cout << "Дата и время последнего обращения к файлу:  " <<
						time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour + 3 << ":" <<
						time.wMinute << ":" << time.wSecond << endl;
					FileTimeToSystemTime(&timeLastWrite, &time);
					cout << "Дата и время последней модификации файла:   " <<
						time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour + 3 << ":" <<
						time.wMinute << ":" <<time.wSecond << endl;
				}
				else {
					cout << "Ошибка! Не удалось получить информацию о файле. Код ошибки: " << GetLastError() << endl;
				}

				system("pause");
				break;
			case 5:
				cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
				cin >> disk_name;

				//SetFileTime

				fileLPC = disk_name.c_str();
				fileT = CreateFileA(fileLPC, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
										nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
				GetSystemTime(&systemTime);
				SystemTimeToFileTime(&systemTime, &fileTime);
				if (SetFileTime(fileT, &fileTime, &fileTime, &fileTime))
				{
					cout << "Атрибуты времени заменены успешно!" << endl;
				}
				else {
					cout << "Ошибка! Код ошибки: " << GetLastError() << endl;
				}

				system("pause");
				break;

			}

			break;

		default:

			break;

		}

	} while (menu != 0);
	return 0;
}
