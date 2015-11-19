/**********************************************************************
  OrcaAnalyseDialog Class Definition

  Copyright (C) 2014 Dagmar Lenk

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.cc/>

  Avogadro is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#ifndef ORCAANALYSEDIALOG_H
#define ORCAANALYSEDIALOG_H

#include <QDialog>
#include <QtCore/QSettings>
#include <avogadro/glwidget.h>
#include <avogadro/extension.h>
#include <avogadro/fragment.h>
#include <openbabel/mol.h>

#include <avogadro/animation.h>

// Include autogenerated ui code
#include "ui_orcaanalysedialog.h"

#include "orcadata.h"
using namespace OpenBabel;

// Forward declaration of Avogadro::Molecule
namespace Avogadro {
class Molecule;
class OrcaSpectra;
}

namespace Avogadro {

class OrcaAnalyseDialog : public QDialog
{
    // The Q_OBJECT macro must be included if a class is to have
    // signals/slots
    Q_OBJECT

public:
    explicit OrcaAnalyseDialog(QWidget *parent = 0, Qt::WindowFlags f = 0 );
    virtual ~OrcaAnalyseDialog();


    void setMolecule(Molecule *molecule);
    void setWidget (GLWidget *widget);
    void readSettings(QSettings&);
    void writeSettings(QSettings&) const;

protected:
    QString readOutputFile();

    bool createAnimation();

    void setAnimationStarted (bool toggle) {m_animationStarted = toggle;}
    bool animationStarted() {return m_animationStarted;}
    void setFramesChecked(bool toggle) {m_framesOK = toggle;}
    bool checkFrames(){return m_framesOK;}
    void setCoordsChecked(bool toggle) {m_coordsOK = toggle;}
    bool checkCoords(){return m_coordsOK;}

private slots:
    void loadFile();

    void updateVibrations();

    void plotSpectra();

    void startAnimation();
    void stopAnimation();
    void setFps(int);
    void setScale(double);

    void selectVibration(int n, int m);
    void setVibration(int n);
    void forceFileReload(Atom* atom);

    void selectFragment();

    void orcaWarningMessage(const QString &m);
//    void SignalEmitted(Molecule *mol);

Q_SIGNALS:
    /*
     * Signal that the Molecule has changed.
     */
    void moleculeChangedHere(Molecule *newMolecule, int n);
    void vibrationsChanged(OrcaVibrations *vibData);
    void orcaWarning(const QString &m);

private:

    Molecule* m_molecule;
    GLWidget* m_widget;
    OrcaVibrations* vibData;
    OrcaSpectra* m_plotIR;
    QList<Primitive *> m_orcaFragment;

    Animation* m_animation;
    OBMol* m_obmol;

    std::vector<std::vector<Eigen::Vector3d> *> m_curFrames;        // frames given to the avogadro program (perhaps deleted by avogadro !!)
    std::vector<std::vector<Eigen::Vector3d> *> m_curConformers;    // conformers given to the avogadro program (perhaps deleted by avogadro!!!)

    std::vector< std::vector< Eigen::Vector3d> > m_orcaFrames;      // save copy of frames
    std::vector< std::vector< Eigen::Vector3d> > m_orcaConformer;   // save copy of conformers

    QWidget *m_vibWidget;
    QWidget *m_orbitalWidget;

    QString m_savePath;
    QString m_saveFilter;

    QLabel *m_freqLabel;
    QLabel *m_fileLabel;

    int m_selectFreq;
    int m_modeOffset;

    int m_nFrames;
    qreal m_freqScale;


    int m_nShells;
    int m_nBasisFunctions;
    int m_nBasisGroups;

    bool m_openShell;

    std::vector<double>  energyEh, energyeV;
    std::vector<double>  occ;
    std::vector<double>  energyBEh, energyBeV;
    std::vector<double>  occB;

    bool m_animationStarted;
    bool m_animationOptionChanged;

    bool m_unitCellRead;
    bool m_fragment;
    bool m_geoRead;

    bool m_orbRead;
    bool m_freqRead;
    bool m_IRRead;
    bool m_ramanRead;
    bool m_modesRead;


    bool m_framesOK;
    bool m_coordsOK;
    bool m_orbitalsOK;

    // This member provides access to all ui elements
    Ui::OrcaAnalyseDialog ui;
};
}
#endif