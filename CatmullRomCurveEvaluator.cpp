#include "CatmullRomCurveEvaluator.h"
#include "mat.h"
#include "vec.h"

void CatmullRomCurveEvaluator::evaluateCurve(const std::vector<Point>& ctrlPts,
	std::vector<Point>& evalCurvePts,
	const float& aniLength,
	const bool& beWrap) const
{
	evalCurvePts.clear();

	int numPts = ctrlPts.size();

	std::vector<Point> ctrl_pts;
	if (beWrap) {
		Point start1(ctrlPts[numPts - 2].x - aniLength, ctrlPts[numPts - 2].y);
		Point start2(ctrlPts[numPts - 1].x - aniLength, ctrlPts[numPts - 1].y);
		Point end1(ctrlPts[0].x + aniLength, ctrlPts[0].y);
		Point end2(ctrlPts[1].x + aniLength, ctrlPts[1].y);
		ctrl_pts.push_back(start1);
		ctrl_pts.push_back(start2);
		ctrl_pts.insert(ctrl_pts.end(), ctrlPts.begin(), ctrlPts.end());
		ctrl_pts.push_back(end1);
		ctrl_pts.push_back(end2);
	}
	else {
		ctrl_pts.push_back(Point(0, ctrlPts.front().y));
		ctrl_pts.insert(ctrl_pts.end(), ctrlPts.begin(), ctrlPts.end());
		ctrl_pts.push_back(Point(aniLength, ctrlPts.back().y));
	}

	const Mat4f basis = Mat4f(
		-1, 3, -3, 1,
		2, -5, 4, -1,
		-1, 0, 1, 0,
		0, 2, 0, 0) / 2.0;

	const int SEGMENT = 100;
	int index;
	for (index = 0; index + 3 < ctrl_pts.size(); index++) {

		const Vec4f px(ctrl_pts[index].x, ctrl_pts[index + 1].x,
			ctrl_pts[index + 2].x, ctrl_pts[index + 3].x);
		const Vec4f py(ctrl_pts[index].y, ctrl_pts[index + 1].y,
			ctrl_pts[index + 2].y, ctrl_pts[index + 3].y);

		for (int i = 0; i < SEGMENT; i++) {
			float t = i / (float) SEGMENT;
			const Vec4f time(t*t*t, t*t, t, 1);

			Point eval_pt(time * basis * px, time * basis * py);
			evalCurvePts.push_back(eval_pt);
		}
	}

	if (!beWrap) {
		evalCurvePts.push_back(Point(0.0, ctrlPts.front().y));
		evalCurvePts.push_back(Point(aniLength, ctrlPts.back().y));
	}
}