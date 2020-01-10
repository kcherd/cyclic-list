# cyclic-list
Шаблон – двоичный файл, содержащий двусвязный циклический список объектов. Тип хранимого в файле объекта – параметр шаблона. В начале файла расположен  файловый указатель на первый элемент списка. Элемент списка содержит 2 файловых указателя на следующий и предыдущий элементы, за которыми следует объект. 
Класс двоичного файла, производный от fstream. Двоичный файл содержит заданную структуру данных с типом хранимых объектов - параметром шаблона. Программа должна выполнять операции создания файла, просмотра, добавления, удаления, обновления и сортировки объектов заданного при генерации типа. Предполагается, что операции сравнения хранимых объектов переопределены стандартным образом (в виде операций <,>  и т.д.). Для позиционирования в потоке можно использовать методы seekg(long,mode) и long tellg(), для хранимого объекта переопределен метод fstream << object который записывает объект с текущей позиции в открытый двоичный поток и метод fstream >> object, который читает содержимое объекта с текущей позиции открытого потока.
