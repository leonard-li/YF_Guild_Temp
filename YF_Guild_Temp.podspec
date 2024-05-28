
Pod::Spec.new do |spec|

  spec.name         = "YF_Guild_Temp"
  spec.version      = "2.0.5"
  spec.summary      = "公会系统"

  spec.description  = <<-DESC
  iOS公会系统功能库
                   DESC

  spec.homepage     = "https://github.com/leonard-li/YF_Guild_Temp.git"


  spec.license      = { :type => "MIT", :file => "LICENSE" }

  spec.author             = { "leonard.li" => "495145872@qq.com" }

  spec.ios.deployment_target = "9.0"

  spec.source       = { :git => "https://github.com/leonard-li/YF_Guild_Temp.git", :tag => spec.version }

  spec.vendored_frameworks = 'YFGuild.framework'

  spec.requires_arc = true

  spec.dependency "YF_Auth", '>= 2.3.1'
  spec.resource_bundles = {
    'YF_GuildResources' => ['Resources/PrivacyInfo.xcprivacy']
  }

end
