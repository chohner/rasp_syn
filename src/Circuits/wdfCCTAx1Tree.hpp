/*
 ==============================================================================

 This file is part of the RT-WDF library.
 Copyright (c) 2015,2016 - Maximilian Rest

 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3

 Details of these licenses can be found at: www.gnu.org/licenses

 RT-WDF is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 -----------------------------------------------------------------------------
 To release a closed-source product which uses RT-WDF, commercial licenses are
 available: write to rt-wdf@e-rm.de for more information.

 ==============================================================================

 wdfCCTAx1Tree.h
 auto-generated by MATLAB wdfLibrary version 0.0.2 on 26-Jan-2016 15:02:45
 for circuit Dempwolf_CCTA

 ==============================================================================
*/


#pragma once
#include "../rt-wdf_lib/Libs/rt-wdf/rt-wdf.h"


using namespace arma;

class wdfCCTAx1Tree : public wdfTree {

private:
    std::unique_ptr<wdfTerminatedResVSource> Vin;
    std::unique_ptr<wdfTerminatedResVSource> E;
    std::unique_ptr<wdfTerminatedCap> CI;
    std::unique_ptr<wdfTerminatedRes> RI;
    std::unique_ptr<wdfTerminatedRes> RG;
    std::unique_ptr<wdfTerminatedCap> CGK;
    std::unique_ptr<wdfTerminatedCap> CGP;
    std::unique_ptr<wdfTerminatedCap> CPK;
    std::unique_ptr<wdfTerminatedRes> RK;
    std::unique_ptr<wdfTerminatedCap> CK;
    std::unique_ptr<wdfTerminatedCap> CO;
    std::unique_ptr<wdfTerminatedRes> RO;
    std::unique_ptr<wdfTerminatedSeries> subtree4a;
    std::unique_ptr<wdfTerminatedParallel> subtree4b;
    std::unique_ptr<wdfTerminatedSeries> tree4;
    std::unique_ptr<wdfTerminatedSeries> subtree5a;
    std::unique_ptr<wdfTerminatedParallel> tree5;
    std::unique_ptr<wdfTerminatedParallel> tree6;
    std::string treeName = "Dempwolf CCTA - 44100 Hz";

public:
    wdfCCTAx1Tree( ) {

        setSamplerate( 44100 );

        paramData inputGain;
        inputGain.name = "Input Gain";
        inputGain.ID = 0;
        inputGain.type = doubleParam;
        inputGain.value = 0.1;
        inputGain.units = " ";
        inputGain.lowLim = 0;
        inputGain.highLim = 2;
        params.push_back(inputGain);

        Vin.reset( new wdfTerminatedResVSource(0, 1) );
        E.reset( new wdfTerminatedResVSource(250, 100000) );
        CI.reset( new wdfTerminatedCap(1.000000e-07, 1) );
        RI.reset( new wdfTerminatedRes(1000000) );
        RG.reset( new wdfTerminatedRes(20000) );
        CGK.reset( new wdfTerminatedCap(1.600000e-12, 1) );
        CGP.reset( new wdfTerminatedCap(1.700000e-12, 1) );
        CPK.reset( new wdfTerminatedCap(4.600000e-13, 1) );
        RK.reset( new wdfTerminatedRes(1500) );
        CK.reset( new wdfTerminatedCap(1.000000e-05, 1) );
        CO.reset( new wdfTerminatedCap(1.000000e-08, 1) );
        RO.reset( new wdfTerminatedRes(1000000) );
        subtree4a.reset( new wdfTerminatedSeries( CI.get(), Vin.get() ) );
        subtree4b.reset( new wdfTerminatedParallel( RI.get(), subtree4a.get() ) );
        tree4.reset( new wdfTerminatedSeries( RG.get(), subtree4b.get() ) );
        subtree5a.reset( new wdfTerminatedSeries( RO.get(), CO.get() ) );
        tree5.reset( new wdfTerminatedParallel( E.get(), subtree5a.get() ) );
        tree6.reset( new wdfTerminatedParallel( CK.get(), RK.get() ) );

        subtreeCount = 6;
        subtreeEntryNodes = new wdfTreeNode*[subtreeCount];
        subtreeEntryNodes[0] = CGP.get();
        subtreeEntryNodes[1] = CGK.get();
        subtreeEntryNodes[2] = CPK.get();
        subtreeEntryNodes[3] = tree4.get();
        subtreeEntryNodes[4] = tree5.get();
        subtreeEntryNodes[5] = tree6.get();
        root.reset( new wdfRootNL(subtreeCount,{TRI_DW}, 1) );
        Rp = new double[subtreeCount] ();
    }

    ~wdfCCTAx1Tree() {
        Vin.reset();
        E.reset();
        CI.reset();
        RI.reset();
        RG.reset();
        CGK.reset();
        CGP.reset();
        CPK.reset();
        RK.reset();
        CK.reset();
        CO.reset();
        RO.reset();
        subtree4a.reset();
        subtree4b.reset();
        tree4.reset();
        subtree5a.reset();
        tree5.reset();
        tree6.reset();

        delete subtreeEntryNodes;
        root.reset();
        delete Rp;
    }

    const char* getTreeIdentifier() {
        return treeName.c_str();

    }

    int setRootMatrData( matData* rootMats, double *Rp ) {

        //------------------------- S matrix -------------------------
        if (rootMats->Smat.is_empty()) {
            return -1;
        }
        if (rootMats->Smat.n_cols != 8) {
            return -1;
        }
        if (rootMats->Smat.n_rows != 8) {
            return -1;
        }

        rootMats->Smat.zeros();

        rootMats->Smat.at(0,0) =  9.7786918485531126865595e-01;
        rootMats->Smat.at(0,1) =  2.8360551912666421506964e-04;
        rootMats->Smat.at(0,2) =  2.9651918176569182434080e-04;
        rootMats->Smat.at(0,3) =  4.0022410848426969240269e-08;
        rootMats->Smat.at(0,4) =  8.0246108567949678194026e-05;
        rootMats->Smat.at(0,5) =  1.2873640289463854520773e-05;
        rootMats->Smat.at(0,6) =  2.1754049854354751136754e-02;
        rootMats->Smat.at(0,7) = -2.1766923494644090097960e-02;
        rootMats->Smat.at(1,0) =  2.8360551912666421506964e-04;
        rootMats->Smat.at(1,1) =  9.0475474071387418373291e-01;
        rootMats->Smat.at(1,2) = -2.8555640201110833687956e-04;
        rootMats->Smat.at(1,3) =  2.6879898900954195739219e-04;
        rootMats->Smat.at(1,4) =  1.1506443119883704263431e-08;
        rootMats->Smat.at(1,5) =  9.4690903895104830412244e-02;
        rootMats->Smat.at(1,6) =  1.9393764939629207952841e-06;
        rootMats->Smat.at(1,7) = -9.4692843271598783894127e-02;
        rootMats->Smat.at(2,0) =  1.9775855793363468215773e+00;
        rootMats->Smat.at(2,1) = -1.9044711351948002686640e+00;
        rootMats->Smat.at(2,2) = -9.9941792441622334663975e-01;
        rootMats->Smat.at(2,3) = -2.6875896659869015796127e-04;
        rootMats->Smat.at(2,4) =  8.0234602124829791278647e-05;
        rootMats->Smat.at(2,5) = -9.4678030254824005473857e-02;
        rootMats->Smat.at(2,6) =  2.1752110477860783777082e-02;
        rootMats->Smat.at(2,7) =  7.2925919776963249452351e-02;
        rootMats->Smat.at(3,0) =  2.8360551905064456659419e-04;
        rootMats->Smat.at(3,1) =  1.9047547407138740727106e+00;
        rootMats->Smat.at(3,2) = -2.8555640201110828266945e-04;
        rootMats->Smat.at(3,3) = -9.9973120101099044454429e-01;
        rootMats->Smat.at(3,4) =  1.1506443119883700954709e-08;
        rootMats->Smat.at(3,5) =  9.4690903895104802656668e-02;
        rootMats->Smat.at(3,6) =  1.9393764939629199482512e-06;
        rootMats->Smat.at(3,7) = -9.4692843271598742260764e-02;
        rootMats->Smat.at(4,0) =  1.9778691848553116017229e+00;
        rootMats->Smat.at(4,1) =  2.8360551907432972199366e-04;
        rootMats->Smat.at(4,2) =  2.9651918176567539867788e-04;
        rootMats->Smat.at(4,3) =  4.0022410851769407572249e-08;
        rootMats->Smat.at(4,4) = -9.9991975389143217256560e-01;
        rootMats->Smat.at(4,5) =  1.2873640280804999231094e-05;
        rootMats->Smat.at(4,6) =  2.1754049854354751136754e-02;
        rootMats->Smat.at(4,7) = -2.1766923494635527502883e-02;
        rootMats->Smat.at(5,0) =  2.5894510743434186747849e-04;
        rootMats->Smat.at(5,1) =  1.9046474603023129112955e+00;
        rootMats->Smat.at(5,2) = -2.8554401396834610833003e-04;
        rootMats->Smat.at(5,3) =  2.6878384959786230917062e-04;
        rootMats->Smat.at(5,4) =  1.0505920891759798301379e-08;
        rootMats->Smat.at(5,5) = -9.0520178816587937298266e-01;
        rootMats->Smat.at(5,6) =  2.6588400787508344955959e-05;
        rootMats->Smat.at(5,7) =  1.9051751997650916425897e+00;
        rootMats->Smat.at(6,0) =  1.9778445244434972316583e+00;
        rootMats->Smat.at(6,1) =  1.7632510751330922609166e-04;
        rootMats->Smat.at(6,2) =  2.9653156980843735617687e-04;
        rootMats->Smat.at(6,3) =  2.4882999172278188190907e-08;
        rootMats->Smat.at(6,4) =  8.0245108045721554794298e-05;
        rootMats->Smat.at(6,5) =  1.2018157929636507546059e-04;
        rootMats->Smat.at(6,6) = -9.7822130112135208257484e-01;
        rootMats->Smat.at(6,7) =  1.9781011195420559189984e+00;
        rootMats->Smat.at(7,0) = -2.4660411814173813818381e-05;
        rootMats->Smat.at(7,1) = -1.0728041156147896434316e-04;
        rootMats->Smat.at(7,2) =  1.2388042762112388552517e-08;
        rootMats->Smat.at(7,3) = -1.5139411679555904905243e-08;
        rootMats->Smat.at(7,4) = -1.0005222281242661992090e-09;
        rootMats->Smat.at(7,5) =  1.0730793901592063782635e-04;
        rootMats->Smat.at(7,6) =  2.4649024293630154136938e-05;
        rootMats->Smat.at(7,7) =  9.9986804303669041260605e-01;

        //------------------------- E matrix -------------------------
        if (rootMats->Emat.is_empty()) {
            return -1;
        }
        if (rootMats->Emat.n_rows != 2) {
            return -1;
        }
        if (rootMats->Emat.n_cols != 6) {
            return -1;
        }

        rootMats->Emat.zeros();

        rootMats->Emat.at(0,0) =  1.3360564445206507197539e-02;
        rootMats->Emat.at(0,1) =  3.7975983925401523579567e-05;
        rootMats->Emat.at(0,2) =  3.6261296511401557539356e-03;
        rootMats->Emat.at(0,3) =  1.3322588464050365633651e-02;
        rootMats->Emat.at(0,4) =  9.8301330590364521810898e-01;
        rootMats->Emat.at(0,5) = -9.9633589436768987823712e-01;
        rootMats->Emat.at(1,0) = -2.9583338247769854802149e-03;
        rootMats->Emat.at(1,1) =  2.8222901719512083484886e-03;
        rootMats->Emat.at(1,2) =  1.0918095378670010349117e-05;
        rootMats->Emat.at(1,3) =  9.9421937600327647821530e-01;
        rootMats->Emat.at(1,4) =  2.9474157299509556873218e-03;
        rootMats->Emat.at(1,5) = -9.9716679173322730900253e-01;

        //------------------------- F matrix -------------------------
        if (rootMats->Fmat.is_empty()) {
            return -1;
        }
        if (rootMats->Fmat.n_rows != 2) {
            return -1;
        }
        if (rootMats->Fmat.n_cols != 2) {
            return -1;
        }

        rootMats->Fmat.zeros();

        rootMats->Fmat.at(0,0) = -8.9375176258014311315492e+04;
        rootMats->Fmat.at(0,1) = -2.6910419448615562032501e+02;
        rootMats->Fmat.at(1,0) = -2.6910419448615562032501e+02;
        rootMats->Fmat.at(1,1) = -1.9999221740017073898343e+04;

        //------------------------- M matrix -------------------------
        if (rootMats->Mmat.is_empty()) {
            return -1;
        }
        if (rootMats->Mmat.n_rows != 6) {
            return -1;
        }
        if (rootMats->Mmat.n_cols != 6) {
            return -1;
        }

        rootMats->Mmat.zeros();

        rootMats->Mmat.at(0,0) = -9.6736220346003087833253e-01;
        rootMats->Mmat.at(0,1) = -5.5686283760517539184742e-03;
        rootMats->Mmat.at(0,2) =  7.2304231115235591959012e-03;
        rootMats->Mmat.at(0,3) = -1.9617935750785113757644e+00;
        rootMats->Mmat.at(0,4) =  1.9601317803475479806252e+00;
        rootMats->Mmat.at(0,5) =  1.6617947309745806361292e-03;
        rootMats->Mmat.at(1,0) = -5.9166676495549866410251e-03;
        rootMats->Mmat.at(1,1) = -9.9435541965609752779187e-01;
        rootMats->Mmat.at(1,2) =  2.1836190757064365684011e-05;
        rootMats->Mmat.at(1,3) =  1.9884387520065518462076e+00;
        rootMats->Mmat.at(1,4) =  5.8948314598271829567455e-03;
        rootMats->Mmat.at(1,5) = -1.9943335834663789007948e+00;
        rootMats->Mmat.at(2,0) =  2.6721128890413156642403e-02;
        rootMats->Mmat.at(2,1) =  7.5951967850658699192394e-05;
        rootMats->Mmat.at(2,2) = -9.9274774069771976048315e-01;
        rootMats->Mmat.at(2,3) =  2.6645176928040043701218e-02;
        rootMats->Mmat.at(2,4) =  1.9660266118072902141733e+00;
        rootMats->Mmat.at(2,5) = -1.9926717887353193603417e+00;
        rootMats->Mmat.at(3,0) = -5.9166673672606121328621e-03;
        rootMats->Mmat.at(3,1) =  5.6442614915361470975808e-03;
        rootMats->Mmat.at(3,2) =  2.1744597087299356115344e-05;
        rootMats->Mmat.at(3,3) =  9.8843907114121254409156e-01;
        rootMats->Mmat.at(3,4) =  5.8949227714002903552593e-03;
        rootMats->Mmat.at(3,5) =  5.6660060873872097886306e-03;
        rootMats->Mmat.at(4,0) =  2.6721129172704881360456e-02;
        rootMats->Mmat.at(4,1) =  7.5633115484384979827596e-05;
        rootMats->Mmat.at(4,2) =  7.2521677086098282685733e-03;
        rootMats->Mmat.at(4,3) =  2.6645496062698073580499e-02;
        rootMats->Mmat.at(4,4) =  9.6602670311866845054283e-01;
        rootMats->Mmat.at(4,5) =  7.3278008186450360739173e-03;
        rootMats->Mmat.at(5,0) =  2.8229173183041867504254e-10;
        rootMats->Mmat.at(5,1) = -3.1885236627504761833799e-07;
        rootMats->Mmat.at(5,2) = -9.1593670482518128685132e-08;
        rootMats->Mmat.at(5,3) =  3.1913465793808801478776e-07;
        rootMats->Mmat.at(5,4) =  9.1311378681932525323492e-08;
        rootMats->Mmat.at(5,5) =  9.9999958955396339721489e-01;

        //------------------------- N matrix -------------------------
        if (rootMats->Nmat.is_empty()) {
            return -1;
        }
        if (rootMats->Nmat.n_rows != 6) {
            return -1;
        }
        if (rootMats->Nmat.n_cols != 2) {
            return -1;
        }

        rootMats->Nmat.zeros();

        rootMats->Nmat.at(0,0) = -1.7821214412707096198574e+05;
        rootMats->Nmat.at(0,1) =  3.9460235091062902938575e+04;
        rootMats->Nmat.at(1,0) = -5.3820838896544103135966e+02;
        rootMats->Nmat.at(1,1) = -3.9998443480034125968814e+04;
        rootMats->Nmat.at(2,0) = -1.7875035251602862263098e+05;
        rootMats->Nmat.at(2,1) = -5.3820838897121234367660e+02;
        rootMats->Nmat.at(3,0) = -5.3595083031028514142236e+02;
        rootMats->Nmat.at(3,1) = -3.9996184038663188403007e+04;
        rootMats->Nmat.at(4,0) = -1.7874809495735555537976e+05;
        rootMats->Nmat.at(4,1) = -5.3594894760022521040810e+02;
        rootMats->Nmat.at(5,0) =  2.2575586730385714950842e+00;
        rootMats->Nmat.at(5,1) =  2.2594413709967380299304e+00;

        return 0;

    }

    void setInputValue(double signalIn) {
        Vin->Vs = signalIn;
    }

    double getOutputValue() {
        return RO->upPort->getPortVoltage();
    }

    void setParam(size_t paramID, double paramValue) {
        if (paramID == 0) {
            params[0].value = paramValue;
        }
    }
};
