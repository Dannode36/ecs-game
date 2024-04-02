#pragma once
#include <any>
#include <string>

enum class Type : uint8_t
{
	Undefined = 0,
	Color = 1, /*! color */
	File = 2, /*! file */
	Int = 3, /*! int */
	Boolean = 4, /*! bool */
	Float = 5, /*! float */
	String = 6, /*! string */
	Class = 7, /*! class */
	Enum = 8,  /*! 'string' or 'int' with a value in 'propertyType' */
	Object = 9 /*! object */
};

class Property
{
public:
	inline Property();
	inline Property(std::string name, std::any value, Type type);

	inline void setValue(const std::any& value);
	inline void setStrValue(const std::string& value);
	inline void setName(const std::string& name);

	[[nodiscard]] inline const std::type_info& getValueType() const;
	inline std::string getValueTypeInfo();
	[[nodiscard]] inline const std::any& getValue() const;
	template <typename T>
	inline T getValue() const;
	[[nodiscard]] inline const std::string& getName() const;
	[[nodiscard]] inline Type getType() const;
	[[nodiscard]] inline const std::string& getPropertyType() const;

protected:
	inline void setTypeByString(const std::string& str);

	//Project* m_project = nullptr; //Used for resolving 'enum' and 'class' objects
	Type m_type = Type::Undefined;
	std::string m_name{};
	std::string m_propertyType{};
	std::any m_value; //Using std::any to assign any type
};

template<typename T>
T Property::getValue() const
{
	bool isCorrectType = (m_value.type() == typeid(T));

	if (isCorrectType)
	{
		T value = std::any_cast<T>(m_value);
		return value;
	}
	else
	{
		static T defaultValue;
		return defaultValue;
	}
}

Property::Property() : m_name{ "unnamed" }
{

}

Property::Property(std::string name, std::any value, Type type) : m_type{ type }, m_name{ std::move(name) }, m_value{ std::move(value) }
{

}

void Property::setValue(const std::any& value)
{
	m_value = value;
}

/*!
 * Sets the value specifically as string.
 * When not specified as std::string, the default is that the value will be set as char * when adding a value like "test"
 * This function is to make sure the value is added as string.
 * @param value
 */
void Property::setStrValue(const std::string& value)
{
	m_value = value;
}

const std::any& Property::getValue() const
{
	return m_value;
}

void Property::setName(const std::string& name)
{
	m_name = name;
}

const std::string& Property::getName() const
{
	return m_name;
}

/*!
 * Gets the value type as std::value_info.
 * This can easily be compared to types like this:
 * Check if int: getValueType() == typeid(int)
 * @return
 */

const std::type_info& Property::getValueType() const
{
	return m_value.type();
}

/*!
 * Gets the value type as std::string
 * Examples of known types:
 * "i" = int
 * "f" = float
 * "b" = bool
 * @return
 */
std::string Property::getValueTypeInfo()
{
	return m_value.type().name();
}

Type Property::getType() const
{
	return m_type;
}

void Property::setTypeByString(const std::string& str)
{
	if (str == "color")
		m_type = Type::Color;
	else if (str == "file")
		m_type = Type::File;
	else if (str == "int")
		m_type = Type::Int;
	else if (str == "bool")
		m_type = Type::Boolean;
	else if (str == "float")
		m_type = Type::Float;
	else if (str == "string")
		m_type = Type::String;
	else if (str == "class")
		m_type = Type::Class;
	else if (str == "object")
		m_type = Type::Object;
	else
		m_type = Type::Undefined;
}

const std::string& Property::getPropertyType() const
{
	return m_propertyType;
}