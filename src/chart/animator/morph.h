#ifndef MORPH_H
#define MORPH_H

#include "base/anim/element.h"
#include "base/math/ratio.h"
#include "base/math/interpolation.h"
#include "chart/options/diagramoptions.h"
#include "chart/generator/diagram.h"

namespace Vizzu
{
namespace Anim
{
namespace Morph
{

class AbstractMorph : public ::Anim::IElement
{
protected:
	typedef Diag::Diagram Dia;
	typedef Diag::DiagramOptions Opt;
	typedef Diag::DiagramItem Item;

public:
	AbstractMorph(const Dia &source, const Dia &target, Dia &actual);
	virtual ~AbstractMorph()
	{}

	void transform(double factor) override;
	virtual std::string name() const = 0;
	virtual void transform(const Dia&, const Dia&, Dia&, double) const {}
	virtual void transform(const Opt&, const Opt&, Opt&, double) const {}
	virtual void transform(const Item&, const Item &, Item&, double ) const {}
protected:
	const Dia &source;
	const Dia &target;
	Dia &actual;
};

class CoordinateSystem : public AbstractMorph
{
public:
	using AbstractMorph::AbstractMorph;
	std::string name() const override { return "CoordSys"; }
	void transform(const Opt&, const Opt&, Opt&, double) const override;
};

class Enable : public AbstractMorph
{
public:
	using AbstractMorph::AbstractMorph;
	std::string name() const override { return "Enable"; }
	void transform(const Item&, const Item&, Item&, double) const override;
};

class Shape : public AbstractMorph
{
public:
	using AbstractMorph::AbstractMorph;
	std::string name() const override { return "Shape"; }
	void transform(const Opt&, const Opt&, Opt&, double) const override;
};

class Horizontal : public AbstractMorph
{
public:
	using AbstractMorph::AbstractMorph;
	std::string name() const override { return "Horizontal"; }
	void transform(const Dia&, const Dia&, Dia&, double) const override;
	void transform(const Opt&, const Opt&, Opt&, double) const override;
	void transform(const Item&, const Item&, Item&, double) const override;
};

class Vertical : public AbstractMorph
{
public:
	using AbstractMorph::AbstractMorph;
	std::string name() const override { return "Vertical"; }
	void transform(const Dia&, const Dia&, Dia&, double) const override;
	void transform(const Item&, const Item&, Item&, double) const override;
};

class Color: public AbstractMorph
{
public:
	using AbstractMorph::AbstractMorph;
	std::string name() const override { return "Color"; }
	void transform(const Dia&, const Dia&, Dia&, double) const override;
	void transform(const Opt&, const Opt&, Opt&, double) const override;
	void transform(const Item&, const Item&, Item&, double) const override;
};

}
}
}

#endif