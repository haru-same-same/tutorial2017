# Declare the package name:
atlas_subdir( MyAnalysisExample )

# Declare the package's dependencies:
atlas_depends_on_subdirs( PUBLIC
			  Control/AthenaBaseComps
			  PRIVATE
			  GaudiKernel
			  Event/xAOD/xAODEventInfo
			  Event/xAOD/xAODMuon
			  MuonSpectrometer/MuonIdHelpers
			  MuonSpectrometer/MuonReconstruction/MuonRecEvent/MuonPrepRawData 
              PhysicsAnalysis/MuonID/MuonSelectorTools
)

# External dependencies:
find_package( ROOT COMPONENTS Core Tree MathCore Hist RIO pthread )


atlas_add_component( MyAnalysisExample
             xAODMuon
		     src/components/*.cxx
		     src/*.cxx
		     INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
		     LINK_LIBRARIES AthenaBaseComps ${ROOT_INCLUDE_DIRS} GaudiKernel xAODEventInfo xAODMuon MuonIdHelpersLib MuonPrepRawData 
             MuonSelectorToolsLib
             MuonIdHelpersLib
             MuonPrepRawData)

# Install files from the package:
atlas_install_joboptions( share/MyAnalysisAlg_options.py )
