#include "BezierCurveEvaluator.h"
#include "linearcurveevaluator.h"
#include "mat.h"
#include "vec.h"

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ctrlPts,
	std::vector<Point>& evalCurvePts,
	const float& aniLength,
	const bool& beWrap) const
{
	int numCtrPt = ctrlPts.size();
	LinearCurveEvaluator linearCurveEvaluator;
	if (numCtrPt < 4) {
		linearCurveEvaluator.evaluateCurve(ctrlPts, evalCurvePts, aniLength, beWrap);
		return;
	}
	evalCurvePts.clear();
	std::vector<Point> ctrl_pts(ctrlPts);

	if (beWrap) {
		ctrl_pts.push_back(Point(ctrlPts.front().x + aniLength, ctrlPts.front().y));
	}

	numCtrPt = ctrl_pts.size();

	Mat4f bezier_basis_matrix(
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 3, 0, 0,
		1, 0, 0, 0);

	const int SEGMENT = 100;
	int index;
	bool wrapped = false;
	for (index = 0; index+3 < numCtrPt; index += 3) {

		evalCurvePts.push_back(ctrl_pts[index]);
		evalCurvePts.push_back(ctrl_pts[index+3]);

		const Vec4f px(ctrl_pts[index].x, ctrl_pts[index + 1].x,
			ctrl_pts[index + 2].x, ctrl_pts[index + 3].x);
		const Vec4f py(ctrl_pts[index].y, ctrl_pts[index + 1].y,
			ctrl_pts[index + 2].y, ctrl_pts[index + 3].y);

		for (int i = 0; i < SEGMENT; i++) {
			float t = i / (float)SEGMENT;
			const Vec4f time(t*t*t, t*t, t, 1);

			Point eval_pt(time * bezier_basis_matrix * px, time * bezier_basis_matrix * py);
			if (eval_pt.x > aniLength && beWrap) {
				float xMod = fmod(eval_pt.x, aniLength);
				if (!wrapped) {
					Point prevPoint(evalCurvePts.back());
					evalCurvePts.push_back(Point(prevPoint.x - aniLength, prevPoint.y));
					evalCurvePts.push_back(eval_pt);
					wrapped = true;
				}
				eval_pt.x = xMod;
			}
			evalCurvePts.push_back(eval_pt);
		}
	}	

	while (index < ctrl_pts.size()) {
		evalCurvePts.push_back(ctrl_pts[index]);
		index++;
	}

	if (!beWrap) {
		evalCurvePts.push_back(Point(0.0, ctrlPts.front().y));
		evalCurvePts.push_back(Point(aniLength, ctrlPts.back().y));
	}
	else if (!wrapped) {
		float ratio = ctrlPts.front().x / (ctrlPts.front().x + aniLength - ctrlPts.back().x);
		float wrapped_y = ctrlPts.back().y + (ctrlPts.front().y - ctrlPts.back().y) * ratio;
		evalCurvePts.push_back(Point(0.0, wrapped_y));
		evalCurvePts.push_back(Point(aniLength, wrapped_y));
	}

}