#include "targetShapeSet.h"

Shape convertToTargetShapeSet(Shape shape, const ShapeSet& targetShapeSet) {
	if (targetShapeSet.find(shape) != targetShapeSet.end()) {
		return shape;
	}
	Shape basicShape = getBasicShape(shape);
	if (targetShapeSet.find(basicShape) == targetShapeSet.end()) {
		throw std::invalid_argument(fmt::format("Target shape set must contain basic shape {}.", basicShape));
	}
	return basicShape;
}

ShapeSet convertToTargetShapeSet(const ShapeSet& shapes, const ShapeSet& targetShapeSet) {
	ShapeSet result;
	for (Shape shape : shapes) {
		result.insert(convertToTargetShapeSet(shape, targetShapeSet));
	}
	return result;
}

ContinuousTimeline<ShapeRule> convertToTargetShapeSet(const ContinuousTimeline<ShapeRule>& shapeRules, const ShapeSet& targetShapeSet) {
	ContinuousTimeline<ShapeRule> result(shapeRules);
	for (const auto& timedShapeRule : shapeRules) {
		ShapeRule rule = timedShapeRule.getValue();
		std::get<ShapeSet>(rule) = convertToTargetShapeSet(std::get<ShapeSet>(rule), targetShapeSet);
		result.set(timedShapeRule.getTimeRange(), rule);
	}
	return result;
}

JoiningContinuousTimeline<Shape> convertToTargetShapeSet(const JoiningContinuousTimeline<Shape>& shapes, const ShapeSet& targetShapeSet) {
	JoiningContinuousTimeline<Shape> result(shapes);
	for (const auto& timedShape : shapes) {
		result.set(timedShape.getTimeRange(), convertToTargetShapeSet(timedShape.getValue(), targetShapeSet));
	}
	return result;
}
