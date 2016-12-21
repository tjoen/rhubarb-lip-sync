#pragma once

#include <set>
#include "Shape.h"
#include "Timeline.h"
#include "Phone.h"

// Returns the basic shape (A-F) that most closely resembles the specified shape.
Shape getBasicShape(Shape shape);

// Returns the mouth shape that results from relaxing the specified shape.
Shape relax(Shape shape);

// A set of mouth shapes that can be used to represent a certain sound.
// The actual selection will be performed based on similarity with the previous or next shape.
using ShapeSet = std::set<Shape>;

// Gets the shape from a non-empty set of shapes that most closely resembles a reference shape.
Shape getClosestShape(Shape reference, ShapeSet shapes);

// Indicates how to time a tween between two mouth shapes
enum class TweenTiming {
	// Tween should end at the original transition
	Early,

	// Tween should overlap both original mouth shapes equally
	Centered,

	// Tween should begin at the original transition
	Late
};

// Returns the tween shape and timing to use to transition between the specified two mouth shapes.
boost::optional<std::pair<Shape, TweenTiming>> getTween(Shape first, Shape second);

// Returns the shape set(s) to use for a given phone.
// The resulting timeline will always cover the entire duration of the phone (starting at 0 cs).
// It may extend into the negative time range if animation is required prior to the sound being heard.
Timeline<ShapeSet> getShapeSets(Phone phone, centiseconds duration, centiseconds previousDuration);
