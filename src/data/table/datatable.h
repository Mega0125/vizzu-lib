#ifndef DATATABLE_H
#define DATATABLE_H

#include <map>
#include <string>
#include <span>

#include "table.h"
#include "columninfo.h"

namespace Vizzu
{
namespace Data
{

enum class SortType : uint8_t
{
	AsSeen,
	Natural
};

class DataCube;
class TextTable;

class DataTable : public Table<double>
{
public:
	typedef Table<double> Base;

	struct DataIndex
	{
		ColumnIndex value;
		ColumnInfo::Type type;

		DataIndex(ColumnIndex value, ColumnInfo::Type type)
			: value(value), type(type) {}
		DataIndex() :
		    value((size_t)-1),
		    type(ColumnInfo::Type::Continous)
		{}
		bool isInvalid() const { return value == (size_t)-1; }
	};

	DataTable();
	explicit DataTable(const TextTable &table);
	const ColumnInfo &getInfo(ColumnIndex index) const;
	DataIndex getIndex(ColumnIndex index) const;
	ColumnIndex getColumn(const std::string &name) const;
	DataIndex getIndex(const std::string &name) const;

	DataIndex addColumn(const std::string &name,
	    const std::span<double> &values);
	DataIndex addColumn(const std::string &name,
	    const std::span<std::string> &values);
	DataIndex addColumn(const std::string &name,
	    const std::span<const char*> &values);

private:
	typedef std::vector<ColumnInfo> Infos;

	SortType discreteSorting;
	std::map<std::string, ColumnIndex> indexByName;
	Infos infos;
	void processHeader(const TextTable &table);
	void fillData(const TextTable &table);
	void sortDiscretes();

	template <typename T>
	DataIndex addTypedColumn(const std::string &name,
	    const std::span<T> &values);
};

}
}

#endif