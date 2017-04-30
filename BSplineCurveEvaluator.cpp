#include "BSplineCurveEvaluator.h"
#include "linearcurveevaluator.h"
#include "mat.h"
#include "vec.h"

void BSplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ctrlPts,
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
	std::vector<Point> deBoorPoints(ctrlPts);
	//deBoorPoints.assign(ctrlPts.begin(), ctrlPts.end());

	if (beWrap) {
		for (int i = 0; i < 3; i++) {
			Point wrappedPoint(ctrlPts[i].x + aniLength, ctrlPts[i].y);
			deBoorPoints.push_back(wrappedPoint);
		}
		Point wrappedPoint(ctrlPts[numCtrPt - 1].x - aniLength, ctrlPts[numCtrPt - 1].y);
		deBoorPoints.insert(deBoorPoints.begin(), wrappedPoint);
	}

	deBoorPoints.insert(deBoorPoints.begin(), deBoorPoints.front());
	deBoorPoints.insert(deBoorPoints.begin(), deBoorPoints.front());
	deBoorPoints.push_back(deBoorPoints.back());
	deBoorPoints.push_back(deBoorPoints.back());

	numCtrPt = deBoorPoints.size();

	vector<Point> ctrl_pts;
	for (int i = 0; i< numCtrPt - 1; i++) {
		if (i != 0) {
			Point tmp1(
				deBoorPoints[i].x * 2 / 3 + deBoorPoints[i + 1].x / 3,
				deBoorPoints[i].y * 2 / 3 + deBoorPoints[i + 1].y / 3);
			Point tmp0(
				(tmp1.x + ctrl_pts.back().x) / 2,
				(tmp1.y + ctrl_pts.back().y) / 2);
			if (i == 1) {
				ctrl_pts.pop_back();
			}
			ctrl_pts.push_back(tmp0);
			if (i != numCtrPt - 1) {
				ctrl_pts.push_back(tmp1);
			}
		}
		if (i != numCtrPt - 1) {
			Point tmp2(
				deBoorPoints[i].x / 3 + deBoorPoints[i + 1].x * 2 / 3,
				deBoorPoints[i].y / 3 + deBoorPoints[i + 1].y * 2 / 3);
			ctrl_pts.push_back(tmp2);
		}
	}
	numCtrPt = ctrl_pts.size();

	Mat4f bezier_basis_matrix(
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 3, 0, 0,
		1, 0, 0, 0);

	const int SEGMENT = 100;
	for (int index = 0; index < numCtrPt - 3; index += 3) {

		const Vec4f px(ctrl_pts[index].x, ctrl_pts[index + 1].x,
			ctrl_pts[index + 2].x, ctrl_pts[index + 3].x);
		const Vec4f py(ctrl_pts[index].y, ctrl_pts[index + 1].y,
			ctrl_pts[index + 2].y, ctrl_pts[index + 3].y);

		for (int i = 0; i < SEGMENT; i++) {
			float t = i / (float) SEGMENT;
			const Vec4f time(t*t*t, t*t, t, 1);

			Point eval_pt(time * bezier_basis_matrix * px, time * bezier_basis_matrix * py);
			evalCurvePts.push_back(eval_pt);
		}
	}
}