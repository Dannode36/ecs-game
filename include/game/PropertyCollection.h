#pragma once
#include "Property.h"
class PropertyCollection
{
public:
	inline PropertyCollection() = default;

	inline explicit PropertyCollection(std::string id);

	inline Property* add(const Property& property);
	inline Property* add(const std::string& name, const std::any& value, Type type);

	inline void remove(const std::string& name);

	inline void setValue(const std::string& name, const std::any& value);
	inline void setProperty(const std::string& name, const Property& value);
	inline void setId(const std::string& id);

	inline bool hasProperty(const std::string& name);
	inline Property* getProperty(const std::string& name);
	inline std::map<std::string, Property>& getProperties();
	inline std::vector<Property*> get();
	template <typename T>
	inline T getValue(const std::string& name);
	[[nodiscard]] inline const std::string& getId() const;
	[[nodiscard]] inline size_t getSize() const;

protected:
	std::string m_id;
	std::map<std::string, Property> m_properties;
};

template<typename T>
T PropertyCollection::getValue(const std::string& name) {
	static T defaultT;
	return (m_properties.count(name) > 0) ? m_properties[name].getValue<T>() : defaultT;
}

PropertyCollection::PropertyCollection(std::string id) : m_id{ std::move(id) }
{

}

Property* PropertyCollection::add(const Property& property) {
	m_properties[property.getName()] = property;
	return &m_properties[property.getName()];
}

Property* PropertyCollection::add(const std::string& name, const std::any& value, Type type) {
	m_properties[name] = { name, value, type };
	return &m_properties[name];
}

void PropertyCollection::remove(const std::string& name) {
	m_properties.erase(name);
}

/*!
 * Sets a value IF the property already exists. Does nothing otherwise.
 * See add() for adding new properties
 * @param name
 * @param value
 */
void PropertyCollection::setValue(const std::string& name, const std::any& value) {
	if (m_properties.count(name) > 0)
		m_properties[name].setValue(value);
}

/*!
 * Overwrites the current property if it exists, or adds it if it doesn't.
 * @param name
 * @param value
 */
void PropertyCollection::setProperty(const std::string& name, const Property& value) {
	m_properties[name] = value;
}

void PropertyCollection::setId(const std::string& id) {
	m_id = id;
}

bool PropertyCollection::hasProperty(const std::string& name) {
	return m_properties.count(name) > 0;
}

Property* PropertyCollection::getProperty(const std::string& name) {
	return (m_properties.count(name) > 0) ? &m_properties[name] : nullptr;
}

std::map<std::string, Property>& PropertyCollection::getProperties() {
	return m_properties;
}

/*!
 * Gets vector of pointers to all the existing properties
 * @return
 */
std::vector<Property*> PropertyCollection::get() {
	std::vector<Property*> props;
	for (auto& i : m_properties) {
		props.emplace_back(&i.second);
	}

	return props;
}

const std::string& PropertyCollection::getId() const {
	return m_id;
}

size_t PropertyCollection::getSize() const {
	return m_properties.size();
}
