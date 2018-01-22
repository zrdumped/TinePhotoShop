#include "QtGuiApplication1.h"

//����ƶ��¼�
void QtGuiApplication1::mouseMoveEvent(QMouseEvent* event) {
	//��������ͼƬ������
	x = event->x() - ImgLabel[CrtID]->x() - ui.canvas->x();// -xoffset;
	y = event->y() - ImgLabel[CrtID]->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
																										 //������Χ����ʾ��Ϣ
	if (x < 0 || x > Qimg[CrtID].width() || y < 0 || y > Qimg[CrtID].height()) {
		statusBar()->showMessage("");
	}
	//��ʾλ�ú���ɫ��Ϣ��Ҷ���Ϣ
	else {
		QRgb rgb = Qimg[CrtID].pixel(x, y);
		if (!isGray)
			statusBar()->showMessage(QString("Pos: (%1, %2); RGB: (%3, %4, %5)").arg
			(QString::number(x), QString::number(y)
				, QString::number(qBlue(rgb)), QString::number(qGreen(rgb)), QString::number(qRed(rgb))));
		else
			statusBar()->showMessage(QString("Pos: (%1, %2); GRAY: %3").arg
			(QString::number(x), QString::number(y)
				, QString::number(qRed(rgb))));
	}
	//�����갴�µĻ�
	//Ϊ�˱�֤�ڲ����µ�ʱ��Ҳ�ܳ�������ƶ�ʱ�������޸��˲������Ƿ���ֻ���˹��ж�
	if (pressed) {
		//������ƶ�״̬
		if (cmd == MOVE && hasMove) {
			//λ��ͼƬ
			int x_tmp = event->x() - RelX - ui.canvas->x();
			int y_tmp = event->y() - RelY - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();
			ImgLabel[CrtID]->move(QPoint(x_tmp, y_tmp));
		}
		else if (cmd == CUT) {
			//cout << lineNum << endl;
			int left = CutLabel->x();
			//int right = CutLabel->x() + CutWidStart;
			int right = CutLabel->x() + CutLabel->width();
			int up = CutLabel->y();
			int down = CutLabel->y() + CutLabel->height();
			RelX = event->x() - ui.canvas->x();// -xoffset;
			RelY = event->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
			switch (lineNum) {
			case NO:case CENTER:return;
			case LEFT_UP:
				if (RelX < ImgLabel[CrtID]->x()) RelX = ImgLabel[CrtID]->x();
				if (RelX > right) RelX = right;
				if (RelY < ImgLabel[CrtID]->y()) RelY = ImgLabel[CrtID]->y();
				if (RelY > down) RelY = down;
				CutLabel->resize(CutLabel->width() + (left - RelX) / 2, CutLabel->height() + (up - RelY));
				CutLabel->move(CutLabel->x() - (left - RelX) / 2, CutLabel->y() - (up - RelY));
				break;
			case LEFT_DOWN:
				if (RelX < ImgLabel[CrtID]->x()) RelX = ImgLabel[CrtID]->x();
				if (RelX > right) RelX = right;
				if (RelY > ImgLabel[CrtID]->y() + ImgLabel[CrtID]->height()) RelY = ImgLabel[CrtID]->y() + ImgLabel[CrtID]->height();
				if (RelY < up) RelY = up;
				CutLabel->resize(CutLabel->width() + (left - RelX) / 2, CutLabel->height() + (RelY - down));
				CutLabel->move(CutLabel->x() - (left - RelX) / 2, CutLabel->y());
				break;
			case RIGHT_UP:
				if (RelX > ImgLabel[CrtID]->x() + ImgLabel[CrtID]->width()) RelX = ImgLabel[CrtID]->x() + ImgLabel[CrtID]->width();
				if (RelX < left) RelX = left;
				if (RelY < ImgLabel[CrtID]->y()) RelY = ImgLabel[CrtID]->y();
				if (RelY > down) RelY = down;
				CutLabel->resize(CutLabel->width() + (RelX - right), CutLabel->height() + (up - RelY));
				CutLabel->move(CutLabel->x(), CutLabel->y() - (up - RelY));
				break;
			case RIGHT_DOWN:
				if (RelX > ImgLabel[CrtID]->x() + ImgLabel[CrtID]->width()) RelX = ImgLabel[CrtID]->x() + ImgLabel[CrtID]->width();
				if (RelX < left) RelX = left;
				if (RelY > ImgLabel[CrtID]->y() + ImgLabel[CrtID]->height()) RelY = ImgLabel[CrtID]->y() + ImgLabel[CrtID]->height();
				if (RelY < up) RelY = up;
				CutLabel->resize(CutLabel->width() + (RelX - right), CutLabel->height() + (RelY - down));
				break;
			case LEFT:
				if (RelX < ImgLabel[CrtID]->x()) RelX = ImgLabel[CrtID]->x();
				if (RelX > right) RelX = right;
				CutLabel->resize(CutLabel->width() + (left - RelX) / 2, CutLabel->height());
				CutLabel->move(CutLabel->x() - (left - RelX) / 2, CutLabel->y());
				break;
			case RIGHT:
				if (RelX > ImgLabel[CrtID]->x() + ImgLabel[CrtID]->width()) RelX = ImgLabel[CrtID]->x() + ImgLabel[CrtID]->width();
				if (RelX < left) RelX = left;
				CutLabel->resize(CutLabel->width() + (RelX - right), CutLabel->height());
				break;
			case UP:
				if (RelY < ImgLabel[CrtID]->y()) RelY = ImgLabel[CrtID]->y();
				if (RelY > down) RelY = down;
				CutLabel->resize(CutLabel->width(), CutLabel->height() + (up - RelY));
				CutLabel->move(CutLabel->x(), CutLabel->y() - (up - RelY));
				break;
			case DOWN:
				if (RelY > ImgLabel[CrtID]->y() + ImgLabel[CrtID]->height()) RelY = ImgLabel[CrtID]->y() + ImgLabel[CrtID]->height();
				if (RelY < up) RelY = up;
				CutLabel->resize(CutLabel->width(), CutLabel->height() + (RelY - down));
				break;
			}
		}
		else if (cmd == RESIZE) {
			int left = CutLabel->x();
			int right = CutLabel->x() + CutLabel->width();
			int up = CutLabel->y();
			int down = CutLabel->y() + CutLabel->height();
			RelX = event->x() - ui.canvas->x();// -xoffset;
			RelY = event->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
			float xRatio, yRatio;
			switch (lineNum) {
			case NO:case CENTER:return;
			case LEFT_UP:
				if (RelX > right) RelX = right;
				if (RelY > down) RelY = down;
				CutLabel->resize(CutLabel->width() + (left - RelX) / 2, CutLabel->height() + (up - RelY));
				CutLabel->move(CutLabel->x() - (left - RelX) / 2, CutLabel->y() - (up - RelY));
				break;
			case LEFT_DOWN:
				if (RelX > right) RelX = right;
				if (RelY < up) RelY = up;
				CutLabel->resize(CutLabel->width() + (left - RelX) / 2, CutLabel->height() + (RelY - down));
				CutLabel->move(CutLabel->x() - (left - RelX) / 2, CutLabel->y());
				break;
			case RIGHT_UP:
				if (RelX < left) RelX = left;
				if (RelY > down) RelY = down;
				CutLabel->resize(CutLabel->width() + (RelX - right), CutLabel->height() + (up - RelY));
				CutLabel->move(CutLabel->x(), CutLabel->y() - (up - RelY));
				break;
			case RIGHT_DOWN:
				if (RelX < left) RelX = left;
				if (RelY < up) RelY = up;
				CutLabel->resize(CutLabel->width() + (RelX - right), CutLabel->height() + (RelY - down));
				break;
			case LEFT:
				if (RelX > right) RelX = right;
				CutLabel->resize(CutLabel->width() + (left - RelX) / 2, CutLabel->height());
				CutLabel->move(CutLabel->x() - (left - RelX) / 2, CutLabel->y());
				break;
			case RIGHT:
				if (RelX < left) RelX = left;
				CutLabel->resize(CutLabel->width() + (RelX - right), CutLabel->height());
				break;
			case UP:
				if (RelY > down) RelY = down;
				CutLabel->resize(CutLabel->width(), CutLabel->height() + (up - RelY));
				CutLabel->move(CutLabel->x(), CutLabel->y() - (up - RelY));
				break;
			case DOWN:
				if (RelY < up) RelY = up;
				CutLabel->resize(CutLabel->width(), CutLabel->height() + (RelY - down));
				break;
			}

			xRatio = (float)CutLabel->width() / (float)ImgBeforeModify.cols;
			yRatio = (float)CutLabel->height() / (float)ImgBeforeModify.rows;
			if (ui.radioButton->isChecked())
				CVimg[CrtID] = MyResize(ImgBeforeModify, xRatio, yRatio, NEAREAST);
			else if (ui.radioButton_3->isChecked())
				CVimg[CrtID] = MyResize(ImgBeforeModify, xRatio, yRatio, BILINEARITY);
			Qimg[CrtID] = ShowImage(CVimg[CrtID], ImgLabel[CrtID], QImage::Format_ARGB32);
			ImgLabel[CrtID]->move(CutLabel->x(), CutLabel->y());

		}
		else if (cmd == ROTATE) {
			if (lineNum == CENTER) {
				//�ƶ���ת����
				RelX = event->x() - ui.canvas->x();// -xoffset;
				RelY = event->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
				int left = CutLabel->x();
				int right = CutLabel->x() + CutLabel->width();
				int up = CutLabel->y();
				int down = CutLabel->y() + CutLabel->height();
				if (RelX < left) RelX = CutLabel->x();
				else if (RelX > right) RelX = right;
				if (RelY < up) RelY = CutLabel->y();
				else if (RelY > down) RelY = down;

				RotateCenter->move(RelX, RelY);
			}
			else {
				RelX = event->x() - RotateCenter->x() - ui.canvas->x();// -xoffset;
				RelY = event->y() - RotateCenter->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
																													 //ʼ�հ���������ת��Ȼ��ƽ�Ƶ���ת������Ӧ��λ��
																													 //cout << RelX << " " << RelY << endl;
				Point2d* newCenter = new Point2d(RotateCenter->x() - CutLabel->x(), RotateCenter->y() - CutLabel->y());
				if (ui.radioButton->isChecked())
					CVimg[CrtID] = MyRotate(ImgBeforeModify, RotateStart->x, RotateStart->y, RelX, RelY, NEAREAST, newCenter);
				else if (ui.radioButton_3->isChecked())
					CVimg[CrtID] = MyRotate(ImgBeforeModify, RotateStart->x, RotateStart->y, RelX, RelY, BILINEARITY, newCenter);
				Qimg[CrtID] = ShowImage(CVimg[CrtID], ImgLabel[CrtID], QImage::Format_ARGB32);
				//cout << newCenter->x << " " << newCenter->y << endl;
				//cout << ImgLabel[CrtID]->x() << endl;
				//cout << RotateCenter->x() << endl;
				//cout << ImgLabel[CrtID]->width() / 2 << endl ;
				//int newX = ImgLabel[CrtID]->x() - (CVimg[CrtID].cols / 2 - RotateCenter->x());
				//int newY = ImgLabel[CrtID]->y() - (CVimg[CrtID].rows / 2 - RotateCenter->y());
				int newX = RotateCenter->x() - newCenter->x;
				int newY = RotateCenter->y() - newCenter->y;
				//int newX = RotateCenter->x() - CutLabel->x() - newCenter->x + ImgLabel[CrtID]->x();
				//int newY = RotateCenter->y() - CutLabel->y() - newCenter->y + ImgLabel[CrtID]->y();
				//cout << ImgLabel[CrtID]->x() << endl;
				ImgLabel[CrtID]->move(newX, newY);
				//cout << ImgLabel[CrtID]->x() << endl << endl;
			}
		}
	}
}

void QtGuiApplication1::mousePressEvent(QMouseEvent* event) {
	//��갴��ʱ״̬Ϊtrue
	pressed = true;
	//������ƶ�״̬
	if (cmd == MOVE) {
		hasMove = true;
		//���㰴��λ�����ͼƬλ��
		RelX = event->x() - ImgLabel[CrtID]->x() - ui.canvas->x();// -xoffset;
		RelY = event->y() - ImgLabel[CrtID]->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
																												//����ڷ�Χ�������
		if (RelX <= Qimg[CrtID].width() && RelX >= 0 && RelY < Qimg[CrtID].height() && RelY > 0) return;
		//�����������ͼƬ��Ѱ��������ڵ�ͼƬ
		for (int i = 0; i < Qimg.size(); i++) {
			if (i == CrtID) continue;
			RelX = event->x() - ImgLabel[i]->x() - ui.canvas->x();// -xoffset;
			RelY = event->y() - ImgLabel[i]->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
																												//��������л�Ϊ��ǰͼƬ���ػ�ֱ��ͼ�����˳�
			if (RelX <= Qimg[i].width() && RelX >= 0 && RelY < Qimg[i].height() && RelY > 0) {
				CrtID = i;
				ChangeLayer(CrtID);
				DrawHistogram();
				ImgLabel[CrtID]->raise();
				return;
			}
		}
		//��û��ѡ���κ�ͼƬ���ƶ�
		hasMove = false;
		return;
	}
	else if (cmd == CUT || cmd == RESIZE) {
		//���㰴��λ����Բü���λ��
		RelX = event->x() - CutLabel->x() - ui.canvas->x();// -xoffset;
		RelY = event->y() - CutLabel->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
																										 //cout << RelX << " " << RelY << endl;
																										 //�����
		if (abs(RelX) < 5 && abs(RelY) < 5) lineNum = LEFT_UP;
		else if (abs(RelX) < 5 && abs(RelY - CutLabel->height()) < 5) lineNum = LEFT_DOWN;
		else if (abs(RelX - CutLabel->width()) < 5 && abs(RelY) < 5) lineNum = RIGHT_UP;
		else if (abs(RelX - CutLabel->width()) < 5 && abs(RelY - CutLabel->height()) < 5) lineNum = RIGHT_DOWN;
		else if (abs(RelX) < 5 && RelY > 0 && RelY < CutLabel->height()) lineNum = LEFT;
		else if (abs(RelX - CutLabel->width()) < 5 && RelY > 0 && RelY < CutLabel->height()) lineNum = RIGHT;
		else if (abs(RelY) < 5 && RelX > 0 && RelX < CutLabel->width()) lineNum = UP;
		else if (abs(RelY - CutLabel->height()) < 5 && RelX > 0 && RelX < CutLabel->width()) lineNum = DOWN;
		else lineNum = NO;
		//cout << lineNum << endl;
	}
	else if (cmd == ROTATE) {
		//���㰴��λ�������ת����λ��
		RelX = event->x() - RotateCenter->x() - ui.canvas->x();// -xoffset;
		RelY = event->y() - RotateCenter->y() - ui.canvas->y() - ui.menuBar->height() - ui.toolBar->height();// -yoffset;
		if (abs(RelX) < 5 && abs(RelY) < 5)lineNum = CENTER;
		else {
			RotateStart = new Point2d(RelX, RelY);
			lineNum = NO;
		}

		/*CVimg[CrtID] = MyRotate(ImgBeforeModify, 200, 0, 200, 200, BILINEARITY, Point2d(RotateCenter->x() - ImgLabel[CrtID]->x(), RotateCenter->y() - ImgLabel[CrtID]->y()));
		Qimg[CrtID] = ShowImage(CVimg[CrtID], ImgLabel[CrtID]);
		ImgLabel[CrtID]->move(CutLabel->x(), CutLabel->y());*/
	}
}

//����ɿ���ʱ��״̬Ϊfalse
void QtGuiApplication1::mouseReleaseEvent(QMouseEvent* event) {
	pressed = false;
}