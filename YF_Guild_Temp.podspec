
Pod::Spec.new do |spec|

  spec.name         = "YF_Guild_Temp"
  spec.version      = "2.0.8"
  spec.summary      = "公会系统"

  spec.description  = <<-DESC
  iOS公会系统功能库
                   DESC

  spec.homepage     = "https://yifants.cn/home"


  spec.license      = { :type => "MIT", :file => "LICENSE" }

  spec.author             = { "leonard.li" => "495145872@qq.com" }

  spec.ios.deployment_target = "9.0"

  spec.source       = { http => "http://mvn.yifants.cn/artifactory/fineboost-ios/guild/2.0.8/YF_Guild.zip" }

  spec.vendored_frameworks = 'YF_Guild/YFGuild.framework'

  spec.requires_arc = true

  spec.dependency "YF_Auth", '>= 2.5.5'
  spec.resource_bundles = {
    'YF_GuildResources' => ['YF_Guild/PrivacyInfo.xcprivacy']
  }

end
